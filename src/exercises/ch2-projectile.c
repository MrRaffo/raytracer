/*
 * Chapter 2, 'Putting it all together', draw the path of the projectile from
 * chapter 1 onto a canvas and export it as a ppm file
 */

#include <stdio.h>

#include <geometry/tuple.h>
#include <graphics/canvas.h>
#include <graphics/color.h>

#include <util/file.h>
#include <util/log.h>
#include <util/mem.h>   // for freeing everything at the end

struct environment {
        struct tuple gravity;
        struct tuple wind;
};

struct projectile {
        struct tuple pos;
        struct tuple vel;
};

int main()
{
        struct tuple grav = tuple_vector(0.0f, -0.1f, 0.0f);
        struct tuple wind = tuple_vector(-0.01f, 0.0f, 0.0f);

        struct tuple position = tuple_point(0.0f, 1.0f, 0.0f);
        struct tuple velocity = tuple_scale(vector_normal(tuple_vector(1.0f, 1.8f, 0.0f)), 11.25f);

        struct environment env = {grav, wind};
        struct projectile proj = {position, velocity};

        struct canvas c = canvas_new(900, 550);
        struct color col = color_new(1.0f, 1.0f, 1.0f);

        printf("Plotting trajectory...\n");

        while (proj.pos.y > 0.0f && proj.pos.x < 900.0f) {
               canvas_write_pixel(c, (int)proj.pos.x, c.h - (int)proj.pos.y, col);
               proj.pos = tuple_add(proj.pos, proj.vel);
               proj.vel = tuple_add(proj.vel, tuple_add(env.gravity, env.wind));
        }

        printf("Exporting to bmp...\n");
        export_to_bmp(c, "img/ch2-projectile.bmp");

        mem_free_all();

        return 0;
}
