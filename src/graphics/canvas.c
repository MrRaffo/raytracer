/*
 * Paul Rafferty 2019
 *
 * The drawing surface
 */

#include <stdio.h>
#include <stdlib.h>     // for itoa
#include <string.h>     // for strncpy

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
 * Create a header for a ppm file, it will follow this format:
 * "P3
 *  WW HH
 *  255"
 * Where WW and HH are strings of the decimal representations of the width and
 * height respectively (not restricted to 2 chars) (P3 is the file format
 * signature and 255 is the max colour component value (R, G and B = 0-255)
 */
char *_create_ppm_header(const struct canvas c)
{
        // get header length:
        int wc = 1, hc = 1, w = c.w, h = c.h;
        while ((w /= 10) > 0) {
                wc++;
        }

        while ((h /= 10) > 0) {
                hc++;
        }

        #define SIG "P3\n"
        #define END "255\n"

        // "P3\n" + (wc + ' ' + hc copy string safe+ '\n') + "255\n" + '\0'
        int len = 3 + wc + 1 + hc + 1 + 4 + 1;
        char *header = (char *)mem_alloc(len);
        char *ptr = header;

        ptr += sprintf(ptr, SIG);
        ptr += sprintf(ptr, "%d %d\n", c.w, c.h);
        ptr += sprintf(ptr, END);

        return header; 
}

/*
 * Return a string formatted to the ppm pixel data format.
 * ie: 255 0 0 252 152 0 212 124 0 22 76
 * where each number is an r, g or b component
 * restricts each line to 12 components before a newline (ppm has a 70 char
 * legacy limit)
 */
char *_create_ppm_data(struct canvas c)
{
        int num_pix = c.w * c.h;

        // reserve space assuming each R, G and B will be 3 chars long
        // and for a space between them
        char *data = (char *)mem_alloc(num_pix * 3 * 4);
        char *ptr = data;

        // ppm files like a line break every 70 chars (legacy stuff), I'll
        // put one every 5 pixels (60 chars worst case scenario, 20 best)
        #define LINE_BREAK 5
        for (int i = 0; i < c.w * c.h; i++) {
                struct color col = c.pixels[i];
                char end = (i % LINE_BREAK == (LINE_BREAK-1)) ? '\n' : ' ';
                ptr += sprintf(ptr, "%s%c", color_to_ppm_string(col), end);
        }

        return data;   
}

/*
 * Export the current canvas to a ppm file with the given name
 * Returns 1 on success, 0 otherwise
 */
const int canvas_export_ppm(const struct canvas c, const char *filename)
{
       
        char *header = _create_ppm_header(c);
        char *data = _create_ppm_data(c); 
        
        // might be wise to create a file.o module to handle all this
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
                log_err("Unable to open file"); // errno?
                return 0;
        }

        /*
        fwrite(header, strlen(header), 1, file);
        fwrite(data, strlen(data), 1, file);
        */

        fprintf(file, "%s%s", header, data);

        fclose(file);

        mem_free(header);
        mem_free(data);

        return 1;
}


