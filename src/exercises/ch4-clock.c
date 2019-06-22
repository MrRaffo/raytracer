/*
 * Chapter 4 - draw a point on each hour of a clock face using matrix
 * translations
 */

#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <graphics/canvas.h>
#include <graphics/color.h>

#include <util/log.h>
#include <util/file.h>
#include <util/mem.h>

int main()
{
        int width = 256, height = 256;
        struct tuple point = tuple_point(1.0f, 0.0f, 0.0f);
        struct color color = color_new(1.0f, 1.0f, 1.0f);
        struct canvas canvas = canvas_new(width, height);

        double angle = 0.0f;

        // adjust size of clock face to fit canvas
        struct matrix scale = matrix_scale((double)width*0.45f, (double)height*0.45f, 1.0f);
        // move centre of clock face to centre to canvas
        struct matrix translate = matrix_translate(width / 2, height / 2, 0.0f);

        for (angle = 0.0f; angle < 2.0f * M_PI; angle += M_PI / 6.0f) {
                struct matrix rotz = matrix_rotate_z(angle);
                struct matrix rotx = matrix_rotate_x(0.0f);
                struct matrix roty = matrix_rotate_y(0.0f);
                struct matrix t = transform(&rotx, &roty, &rotz, &scale, &translate, NULL);
                struct tuple hour = matrix_transform(t, point);
                canvas_write_pixel(canvas, hour.x, hour.y, color);
        }

        export_to_bmp(canvas, "img/ch4-clock.bmp");
        mem_free_all();
}
