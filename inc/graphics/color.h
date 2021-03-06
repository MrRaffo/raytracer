#ifndef __color_h__
#define __color_h__

#include <stdint.h>

/*
 * Representations of colors using tuples
 * r, g and b components represented as numbers between
 * 0.0f and 1.0f
 */

struct color {
        double r;
        double g;
        double b;
};

/* Creation functions */

/* 
 * Create a color from given double values, these should be
 * between 0.0f and 1.0f, but this is not checked or 
 * enforced
 */
struct color color_new(const double r, const double g, const double b);

/* 
 * Create a color giving ints between 0-255 as the components
 * and convert to double to use in struct color
 */
struct color color_newi(const int r, const int g, const int b);

/*
 * Return 1 if two colors RGB components are equal, 0 otherwise
 */
const int color_equal(const struct color c1, const struct color c2);

/*
 * Print a color to the output
 */
void color_print(struct color c);

/*
 * return 32-bit uint representing the colour in bitmap ARGB format
 */
uint32_t color_to_RGBA(struct color c);

/*
 * Produce a string of the colour data, this will format the string to the format
 * used by ppm files ie, (1.0f, 0.0f, 0.5f) becomes "255 0 128"
 */
char *color_to_ppm_string(struct color c);

/*
 * Add the RGB components of two colors together and return the result
 */
struct color color_add(const struct color c1, const struct color c2);

/*
 * Subtract the RGB components of c2 from those of c1 and return the new
 * colour obtained, not communitive
 */
struct color color_subtract(const struct color c1, const struct color c2);

/*
 * Multiply each RGB component of a colour by a scalar double
 */
struct color color_scale(const struct color c1, const double f);

/*
 * Multiply the RGB components of each colour together and return the new
 * colour obtained, also known as the Hadamard Product or Schur Product
 */
struct color color_multiply(const struct color c1, const struct color c2);

#endif //__color_h__
