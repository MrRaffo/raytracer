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
