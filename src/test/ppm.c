#include <stdio.h>
#include <graphics/canvas.h>
#include <util/file.h>

int main()
{
        struct canvas c = canvas_new(5, 3);
        struct color c1 = color_new(1.5f, 0.0f, 0.0f);
        struct color c2 = color_new(0.0f, 0.5f, 0.0f);
        struct color c3 = color_new(-0.5f, 0.0f, 1.0f);

        canvas_write_pixel(c, 0, 0, c1);
        canvas_write_pixel(c, 2, 1, c2);
        canvas_write_pixel(c, 4, 2, c3);
        export_to_ppm(c, "img/test.ppm");

        return 0;
}
