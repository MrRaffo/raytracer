#include <stdio.h>
#include <math.h>

#include <graphics/canvas.h>
#include <graphics/color.h>

#include <geometry/tuple.h>

#include <util/mem.h>
#include <util/log.h>
#include <util/file.h>

#define WIDTH 800
#define HEIGHT 800
#define LIGHT_RADIUS 100

#define TILE_SIZE 8

/* create a cirular pattern of given colour
 * at_edge: how bright the light should be in comparison to the centre (full)
 *      ie, a value of 0.5 will make the light half as bright at the edge,
        and a value of 1.0 will make the light the same at all points
 */
struct canvas make_light_canvas(struct color col, int radius, double at_edge)
{
        int light_size = radius * 2;
        double rf = radius * radius;
        struct canvas light_canvas = canvas_new(light_size, light_size);
        int x, y;
        double brightness = 1.0;
        double step = (1.0 - at_edge) / (double)radius;

        for (x = 0; x < light_size; x++) {
                for (y = 0; y < light_size; y++) {
                        double xf = x - radius;
                        double yf = y - radius;
                        double distf = xf * xf + yf * yf;
                        if (distf < rf) {
                                double dist = fabs(radius - sqrt(distf));
                                brightness = at_edge + dist * step;
                                canvas_write_pixel(light_canvas, x, y, color_scale(col, brightness));
                        }
                }
        }

        return light_canvas;
}

/* make a texture that fades as it goes down the y axis */
struct canvas make_fade_texture(struct color col, int w, int h)
{
        struct canvas texture = canvas_new(w, h);
        double brightness = 1.0;
        double step = brightness / (double)(h * 1);
        struct color white = color_new(1.0, 1.0, 1.0);

        int x, y;
        for (x = 0; x < w; x++) {
                for (y = 0; y < h; y++) {
                        brightness = step * y;
                        struct color pixel = color_subtract(col, color_scale(white, brightness));

                        canvas_write_pixel(texture, x, y, pixel);
                }
        }

        return texture;
}


/* create a chequered pattern, alternating between col1 and col2, with tiles of
 * size tile_size */
struct canvas make_texture_canvas(struct color col1, struct color col2, int w, int h, int tile_size)
{
        struct canvas texture = canvas_new(w, h);
        struct color current = col1;
        int x, y;

        for (x = 0; x < w; x++) {
                for (y = 0; y < h; y++) {
                        // create a tile pattern
                        if (((x / tile_size) + (y / tile_size)) & 1) {
                                current = col1;
                        } else {
                                current = col2;
                        }

                        canvas_write_pixel(texture, x, y, current);
                }
        }

        return texture;
}

int main()
{
        // set up a canvas with a chequered pattern
        struct color red = color_new(0.0, -0.3, -0.3);
        struct color white = color_new(0.0, 0.0, 0.0);
        struct color yellow_light = color_new(0.5, 0.4, 0.2);
        struct color blue_light = color_new(0.1, 0.1, 0.4);
        struct color white_light = color_new(0.5, 0.5, 0.5);

        struct canvas texture = make_texture_canvas(red, white, WIDTH, HEIGHT, TILE_SIZE);
        struct canvas light1 = make_light_canvas(yellow_light, 200, 0.0);
        struct canvas light2 = make_light_canvas(blue_light, 150, 0.0);
        struct canvas light3 = make_light_canvas(white_light, 300, 0.0);

        export_to_bmp(texture, "img/2d/texture.bmp");
        export_to_bmp(light1, "img/2d/light.bmp");

        // apply light to texture
        canvas_blit_add(texture, light1, 20, 20, 0, 0, 400, 400);
        canvas_blit_add(texture, light2, 400, 100, 0, 0, 300, 300);
        canvas_blit_add(texture, light3, 100, 200, 0, 0, 600, 600);
        
        struct color green = color_new(0.0, 0.8, 0.2);
        struct canvas texture2 = make_fade_texture(green, WIDTH, HEIGHT);
        canvas_blit_add(texture2, light3, 100, 400, 0, 0, 600, 600);

        struct color dark_green1 = color_new(-1.0, -0.2, -0.6);
        struct color dark_green2 = color_new(-1.0, -0.15, -0.6);
        struct canvas texture3 = make_texture_canvas(dark_green1, dark_green2, 900, 300, 8);
        
        struct canvas light4 = make_light_canvas(color_new(1.0, 1.0, 1.0), 100, 0.2);
        struct canvas light5 = make_light_canvas(color_new(0.75, 0.75, 0.75), 100, 0.25);
        struct canvas light6 = make_light_canvas(color_new(0.5, 0.5, 0.5), 100, 0.3);
        struct canvas light7 = make_light_canvas(color_new(0.35, 0.35, 0.35), 100, 0.5);

        canvas_blit_add(texture3, light4, 25, 50, 0, 0, 200, 200);
        canvas_blit_add(texture3, light5, 225, 50, 0, 0, 200, 200);
        canvas_blit_add(texture3, light6, 450, 50, 0, 0, 200, 200);
        canvas_blit_add(texture3, light7, 675, 50, 0, 0, 200, 200);

        export_to_bmp(texture, "img/2d/itslit.bmp");
        export_to_bmp(texture2, "img/2d/fade.bmp");
        export_to_bmp(texture3, "img/2d/darkness.bmp");

        mem_free_all();

        return 0;
}
