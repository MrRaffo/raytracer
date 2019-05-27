#include <stdio.h>

#include <graphics/color.h>
#include <geometry/gmaths.h>    // for float_equal

/* Creation functions */

/* 
 * Create a color from given float values, these should be
 * between 0.0f and 1.0f, but this is not checked or 
 * enforced
 */
const struct color color_new(const float r, const float g, const float b)
{
        const struct color c = {r, g, b};
        return c;
}

/* 
 * Create a color giving ints between 0-255 as the components
 * and convert to float to use in struct color
 */
const struct color color_newi(const int r, const int g, const int b)
{
        float d = 255.0f;
        const struct color c = {(float)r / d, (float)g / d, (float)b / d};
        return c;
}

/*
 * Return 1 if two colors RGB components are equal, 0 otherwise
 */
const int color_equal(const struct color c1, const struct color c2)
{
        if (!float_equal(c1.r, c2.r)) { return 0; }
        if (!float_equal(c1.g, c2.g)) { return 0; }
        if (!float_equal(c1.b, c2.b)) { return 0; }

        return 1;
}

/*
 * Add the RGB components of two colors together and return the result
 */
const struct color color_add(const struct color c1, const struct color c2)
{
        return color_new(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

/*
 * Subtract the RGB components of c2 from those of c1 and return the new
 * colour obtained, not communitive
 */
const struct color color_subtract(const struct color c1, const struct color c2)
{
        return color_new(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

/*

 * Multiply each RGB component of a colour by a scalar float
 */
const struct color color_scale(const struct color c1, const float f)
{
        return color_new(c1.r * f, c1.g * f, c1.b * f);
}

/*
 * Multiply the RGB components of each colour together and return the new
 * colour obtained, also known as the Hadamard Product or Schur Product
 */
const struct color color_multiply(const struct color c1, const struct color c2)
{
        return color_new(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}
