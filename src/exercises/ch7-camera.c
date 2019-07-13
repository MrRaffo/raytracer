#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <scene/world.h>
#include <scene/material.h>
#include <scene/light.h>
#include <scene/camera.h>
#include <geometry/g_object.h>
#include <geometry/ray.h>

#include <util/mem.h>
#include <util/log.h>
#include <util/file.h>

int main()
{
        struct world *w = world_new();
        struct camera c = camera(800, 400, M_PI / 3.0);

        // floor and walls are made from very large spheres
        struct material floor_mat = material();
        floor_mat.color = color_new(1.0, 0.9, 0.9);
        floor_mat.specular = 0.0;
        struct matrix floor_transform = matrix_scale(10.0, 0.01, 10.0);
        
        struct g_object *floor = sphere(floor_mat, floor_transform);

        struct matrix left_t = matrix_translate(0.0, 0.0, 5.0);
        struct matrix left_ry = matrix_rotate_y(-M_PI_4);
        struct matrix left_rx = matrix_rotate_x(M_PI_2);
        struct matrix left_scale = matrix_scale(10.0, 0.01, 10.0);

        struct matrix left_wall_transform = transform(&left_scale, &left_rx,
                                                      &left_ry, &left_t,
                                                      NULL);



        struct g_object *left_wall = sphere(floor_mat, left_wall_transform);

        struct matrix right_ry = matrix_rotate_y(M_PI_4);
        struct matrix right_wall_transform = transform(&left_scale, &left_rx,
                                                       &right_ry, &left_t,
                                                       NULL);

        struct g_object *right_wall = sphere(floor_mat, right_wall_transform);

        // create the objects in foreground
        struct material middle_mat = material();
        middle_mat.color = color_new(0.1, 1.0, 0.5);
        middle_mat.diffuse = 0.7;
        middle_mat.specular = 0.3;
        struct matrix middle_transform = matrix_translate(-0.5, 1.0, 0.5);
        struct g_object *middle_sphere = sphere(middle_mat, middle_transform);

        // right sphere
        struct material right_mat = material();
        right_mat.color = color_new(0.5, 1.0, 0.1);
        right_mat.diffuse = 0.7;
        right_mat.specular = 0.3;
        struct matrix right_scale = matrix_scale(0.5, 0.5, 0.5);
        struct matrix right_translate = matrix_translate(1.5, 0.5, -0.5);
        struct matrix right_transform = transform(&right_scale, &right_translate, NULL);
        struct g_object *right_sphere = sphere(right_mat, right_transform);

        // left sphere
        struct material left_mat = material();
        left_mat.color = color_new(1.0, 0.8, 0.1);
        left_mat.diffuse = 0.7;
        left_mat.specular = 0.3;
        struct matrix left_translate = matrix_translate(-1.5, 0.33, -0.75);
        struct matrix l_scale = matrix_scale(0.33, 0.33, 0.33);
        struct matrix left_transform = transform(&l_scale, &left_translate, NULL);
        struct g_object *left_sphere = sphere(left_mat, left_transform);

        world_add_object(w, left_sphere);
        world_add_object(w, right_sphere);
        world_add_object(w, middle_sphere);
        world_add_object(w, floor);
        world_add_object(w, right_wall);
        world_add_object(w, left_wall);
        
        struct p_light light = p_light_new(tuple_point(-10.0, 10.0, -10.0),
                                           color_new(1.0, 1.0, 1.0));

        struct p_light new_light = p_light_new(tuple_point(10.0, 10.0, -10.0),
                                               color_new(0.0, 0.5, 0.99));

        world_add_light(w, light);
        world_add_light(w, new_light);

        c.transform = matrix_view_transform(tuple_point(0.0, 1.5, -5.0),
                                            tuple_point(0.0, 1.0, 0.0),
                                            tuple_vector(0.0, 1.0, 0.0));

        struct canvas image = camera_render(c, w);

        export_to_bmp(image, "img/shadow-cast.bmp");

        mem_free_all();

        return 0;
}
