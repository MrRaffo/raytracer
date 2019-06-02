/*
 * Paul Rafferty 2019
 */

#ifndef __canvas_h__
#define __canvas_h__

#include <graphics/color.h>

struct canvas {
        const int w;
        const int h;
        struct color *pixels;
};

/*
 * Create a new canvas, every color will be initialized to (0, 0, 0)
 */
struct canvas canvas_new(const int w, const int h);

/*
 * Print the contents of a canvas, for testing purposes
 */
void canvas_print(struct canvas c);

/*
 * Get the value of a pixel at a given position on the canvas
 * Returns (0.0f, 0.0f, 0.0f) on failure
 */
struct color canvas_read_pixel(struct canvas canvas, int x, int y);

/*
 * Write the given color to the given coordinates, returns 1 if successful,
 * 0 otherwise
 */
const int canvas_write_pixel(struct canvas canvas, int x, int y, struct color col);

#endif // __canvas_h__
