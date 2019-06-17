#include <stdio.h>
#include <stdint.h>

#include <graphics/color.h>
#include <geometry/gmaths.h>    // for double_equal
#include <util/mem.h>

/* Creation functions */

/* 
 * Create a color from given double values, these should be
 * between 0.0f and 1.0f, but this is not checked or 
 * enforced
 */
struct color color_new(const double r, const double g, const double b)
{
        const struct color c = {r, g, b};
        return c;
}

/* 
 * Create a color giving ints between 0-255 as the components
 * and convert to double to use in struct color
 */
struct color color_newi(const int r, const int g, const int b)
{
        double d = 255.0f;
        const struct color c = {(double)r / d, (double)g / d, (double)b / d};
        return c;
}

/*
 * Return 1 if two colors RGB components are equal, 0 otherwise
 */
const int color_equal(const struct color c1, const struct color c2)
{
        if (!double_equal(c1.r, c2.r)) { return 0; }
        if (!double_equal(c1.g, c2.g)) { return 0; }
        if (!double_equal(c1.b, c2.b)) { return 0; }

        return 1;
}

/*
 * Print a color to the output
 */
void color_print(struct color c)
{
        fprintf(stdout, "(%.2f, %.2f, %.2f)", c.r, c.g, c.b);
}

// tranform color to 0-255 int, restricting within that range
static const int _clamp_component(const double c)
{
        if (c < 0.0f) return 0;
        if (c >= 1.0f) return 255;

        return (int)(c * 255.0f + 0.5f);
}

/*
 * Produce a string of the colour data, this will format the string to the format
 * used by ppm files ie, (1.0f, 0.0f, 0.5f) becomes "255 0 128"
 */
char *color_to_ppm_string(struct color c)
{
        int r = _clamp_component(c.r);
        int g = _clamp_component(c.g);
        int b = _clamp_component(c.b);

        // 12 = 3 for each component, 2 spaces between them and one for '\0'
        char *cstr = (char *)mem_alloc(12);
        sprintf(cstr, "%d %d %d", r, g, b);

        return cstr;
}

// return 32-bit uint representing the colour in bitmap ARGB format
uint32_t color_to_RGBA(struct color c)
{
        uint32_t val = 0x0;
        val = 0xff << 24 | 
                (_clamp_component(c.r) & 0xff) << 16 | 
                (_clamp_component(c.g) & 0xff) << 8  |
                (_clamp_component(c.b) & 0xff);
        return val;
}

/*
 * Add the RGB components of two colors together and return the result
 */
struct color color_add(const struct color c1, const struct color c2)
{
        return color_new(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

/*
 * Subtract the RGB components of c2 from those of c1 and return the new
 * colour obtained, not communitive
 */
struct color color_subtract(const struct color c1, const struct color c2)
{
        return color_new(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

/*

 * Multiply each RGB component of a colour by a scalar double
 */
struct color color_scale(const struct color c1, const double f)
{
        return color_new(c1.r * f, c1.g * f, c1.b * f);
}

/*
 * Multiply the RGB components of each colour together and return the new
 * colour obtained, also known as the Hadamard Product or Schur Product
 */
struct color color_multiply(const struct color c1, const struct color c2)
{
        return color_new(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}
