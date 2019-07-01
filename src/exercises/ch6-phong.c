#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/ray.h>
#include <geometry/matrix.h>
#include <geometry/g_object.h>

#include <graphics/color.h>
#include <graphics/canvas.h>

#include <scene/light.h>
#include <scene/material.h>

#include <util/mem.h>
#include <util/log.h>
#include <util/file.h>

#define WIDTH 800
#define HEIGHT 800

#define WALL_SIZE 7.0

#define CAM_POS_Z -5.0
#define WALL_POS_Z 10.0

int main()
{
        // canvas and color
        struct canvas canvas = canvas_new(WIDTH, HEIGHT);
        struct color red = color_new(0.7843, 0.0627, 0.1804);

        // object to render
        struct g_object *sphere = test_sphere();
        struct material m = material_new(red, 0.1, 0.9, 0.9, 200.0);
        sphere->material = m;
        //struct matrix move = matrix_translate(0.0, 0.0, 0.0);
        //struct matrix move = matrix_scale(1.0, 1.0, 0.2);
        //struct matrix roty = matrix_rotate_y(0.9);
        //struct matrix rotx = matrix_rotate_x(0.5);
        //struct matrix t = transform(&move, &rotx, &roty, NULL);
        //object_transform(sphere, t);

        // light source
        struct tuple light_pos = tuple_point(-10.0, 10.0, -10.0);
        struct color light_col = color_new(1.0, 1.0, 1.0);
        struct p_light light = p_light_new(light_pos, light_col);

        // camera
        struct tuple cam_pos = tuple_point(0.0, 0.0, CAM_POS_Z);


        // size of pixels in world space
        double pixel_size = WALL_SIZE / WIDTH;
        double half = WALL_SIZE / 2.0;

        // cast the rays
        int x, y;
        for (y = 0; y < HEIGHT; y++) {
                double world_y = half - pixel_size * y;

                for(x = 0; x < WIDTH; x++) {
                        double world_x = -half + pixel_size * x;

                        struct tuple pos = tuple_point(world_x, world_y, WALL_POS_Z);
                        struct ray ray = ray_new(cam_pos, 
                                vector_normal(tuple_subtract(pos, cam_pos)));

                        struct i_list *hits = i_list_new();
                        ray_intersect(ray, sphere, hits);

                        // if there is a hit, colour the pixel
                        if (i_list_hit(hits)) {
                                // ray-object intersection point
                                struct tuple i_point = ray_position(ray, i_list_hit(hits)->t);
                                // object surface normal at intersection point
                                struct tuple obj_n = object_normal_at(sphere, i_point);
                                // eye direction
                                struct tuple eye_v = tuple_negate(ray.dir);
                                
                                struct color col = light_phong(sphere->material, 
                                                light, i_point, eye_v, obj_n);
                                
                                canvas_write_pixel(canvas, x, y, col);
                        }
                }
        }

        export_to_bmp(canvas, "img/phong.bmp");

        mem_print();
        mem_free_all();

        return 0;
}
