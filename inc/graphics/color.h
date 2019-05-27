#ifndef __color_h__
#define __color_h__

/*
 * Representations of colors using tuples
 * r, g and b components represented as numbers between
 * 0.0f and 1.0f
 */

struct color {
        float r;
        float g;
        float b;
};

/* Creation functions */

/* 
 * Create a color from given float values, these should be
 * between 0.0f and 1.0f, but this is not checked or 
 * enforced
 */
const struct color color_new(const float r, const float g, const float b);

/* 
 * Create a color giving ints between 0-255 as the components
 * and convert to float to use in struct color
 */
const struct color color_newi(const int r, const int g, const int b);

#endif //__color_h__
