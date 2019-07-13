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

        // create the sun
        struct color sun_color = color_new(1.0, 1.0, 0.7);
        struct material sun_material = {sun_color, 1.0, 1.0, 0.0, 0.0};
        
        struct matrix sun_translate = matrix_translate(55.0, 0.0, -10.0);
        struct matrix sun_scale = matrix_scale(50.0, 50.0, 50.0);
        struct matrix sun_transform = transform(&sun_scale, &sun_translate, NULL);

        struct g_object *sun = sphere(sun_material, sun_transform);

        // create the earth
        struct color earth_color = color_new(0.08, 0.65, 0.9);
        struct material earth_material = {earth_color, 0.1, 0.9, 0.5, 150.0};

        struct matrix earth_translate = matrix_translate(-4.5, 0.0, -10.0);
        struct matrix earth_scale = matrix_scale(0.35, 0.35, 0.35);
        struct matrix earth_transform = transform(&earth_scale, &earth_translate, NULL);
        
        struct g_object *earth = sphere(earth_material, earth_transform);

        // create the moon
        struct color moon_color = color_new(0.8, 0.8, 0.8);
        struct material moon_material = {moon_color, 0.1, 0.9, 0.0, 500.0};

        struct matrix moon_translate = matrix_translate(-3.5, 0.0, -9.9);
        struct matrix moon_scale = matrix_scale(0.1, 0.1, 0.1);
        struct matrix moon_transform = transform(&moon_scale, &moon_translate, NULL);

        struct g_object *moon = sphere(moon_material, moon_transform);

        // let there be light
        struct p_light l = p_light_new(tuple_point(4.5, 0.0, -9.9), sun_color);

        world_add_object(w, sun);
        world_add_object(w, earth);
        world_add_object(w, moon);
        world_add_light(w, l);

        //struct canvas image = camera_render(c, w);
        //export_to_bmp(image, "img/eclipse.bmp");

        struct world *w2 = world_new();

        sun_translate = matrix_translate(0.0, 25.0, -200.0);
        sun_scale = matrix_scale(6.0, 6.0, 6.0);
        sun_transform = transform(&sun_scale, &sun_translate, NULL);
        object_transform(sun, sun_transform);
        
        earth_translate = matrix_translate(0.0, -1.0, -1.0);
        earth_scale = matrix_scale(1.0, 1.0, 1.0);
        earth_transform = transform(&earth_scale, &earth_translate, NULL);
        object_transform(earth, earth_transform);
        
        moon_translate = matrix_translate(0.0, 0.5, -15.0);
        moon_scale = matrix_scale(1.0, 1.0, 1.0);
        moon_transform = transform(&moon_scale, &moon_translate, NULL);
        object_transform(moon, moon_transform);

        l.position = tuple_point(0.0, 200.0, -190.0);

        // increase visibility, for testing only
        earth->material.ambient = 0.001;
        earth->material.specular = 0.0;
        //moon->material.ambient = 1.0;

        world_add_object(w2, earth);
        world_add_object(w2, moon);
        world_add_object(w2, sun);
        world_add_light(w2, l);

        struct canvas w2img = camera_render(c, w2);
        export_to_bmp(w2img, "img/eclipse2.bmp");


        mem_free_all();

        return 0;
}
