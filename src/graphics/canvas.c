/*
 * Paul Rafferty 2019
 *
 * The drawing surface
 */

#include <stdio.h>

#include <graphics/canvas.h>
#include <graphics/color.h>

#include <util/mem.h>
#include <util/log.h>

/*
 * Create a new canvas, every color will be initialized to (0, 0, 0)
 */
struct canvas canvas_new(const int w, const int h)
{
        struct canvas c = {w, h, NULL};

        c.pixels = (struct color *)mem_alloc(w * h * sizeof(struct color));
        
        int i;
        for (i = 0; i < w * h; i++) {
                c.pixels[i] = color_new(0.0f, 0.0f, 0.0f);
        }

        return c;
}

/*
 * Print the contents of a canvas, for testing purposes
 */
void canvas_print(struct canvas c) 
{
        int i;
        for (i = 0; i < c.w * c.h; i++) {
                color_print(c.pixels[i]);
                if (i % c.w == c.w - 1) {
                        fprintf(stdout, "\n");
                } else {
                        fprintf(stdout, " ");
                }
        }
}

/*
 * Check if a pixel is on the surface of the canvas, checks both x and y
 * coords separately rather than just checking buffer index
 */
int _within_bounds(struct canvas c, int x, int y)
{
        if (x < 0 || x >= c.w || y < 0 || y >= c.h) {
                log_err("canvas - out of bounds pixel access: (%d, %d)", x, y);
                return 0;
        }

        return 1;
}

/*
 * Get the value of a pixel at a given position on the canvas
 * Returns (0.0f, 0.0f, 0.0f) on failure
 */
struct color canvas_read_pixel(struct canvas c, int x, int y)
{
        if(!_within_bounds(c, x, y)) {
                return color_new(0.0f, 0.0f, 0.0f);
        }
        
        return c.pixels[y * c.w + x];
}

/*
 * Write the given color to the given coordinates, returns 1 if successful,
 * 0 otherwise
 */
const int canvas_write_pixel(struct canvas canvas, int x, int y, struct color col)
{       
        if(!_within_bounds(canvas, x, y)) {
                return 0;
        }

        canvas.pixels[y * canvas.w + x] = col;
        return 1;
}

/*
 * blit an area of one canvas onto another, adding the colours together
 */
void canvas_blit_add(struct canvas dest, struct canvas source, 
                     int dx, int dy, int sx, int sy, int sw, int sh)
{
        int x, y;
        struct color newcol;
        for (x = 0; x < sw; x++) {
                for (y = 0; y < sh; y++) {
                        newcol = color_add(canvas_read_pixel(dest, dx+x, dy+y),
                                           canvas_read_pixel(source, sx+x, sy+y));
                        canvas_write_pixel(dest, dx+x, dy+y, newcol);
                }
        }
}
