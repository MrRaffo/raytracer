#include <stdio.h>
#include <graphics/color.h>
#include <geometry/gmaths.h>    // for float_equal
#include <util/log.h>

#include <assert.h>

int TST_ColorNewInt()
{
        struct color col1 = color_newi(200, 150, 100);
        struct color col2 = color_newi(0xff, 0x88, 0x00);

        assert(float_equal(col1.r, 0.7843147f));
        assert(float_equal(col1.g, 0.5882352f));
        assert(float_equal(col1.b, 0.3921568f));
        
        assert(float_equal(col2.r, 1.0f));
        assert(float_equal(col2.g, 0.5333333f));
        assert(float_equal(col2.b, 0.0f));

        log_msg("[Color NewInt] All tests complete - pass!");

        return 1;
}

int TST_ColorEqual()
{
        struct color c1 = color_new(0.34f, 0.12f, 0.99f);
        struct color c2 = color_new(0.34f, 0.12f, 0.99000002f);
        struct color c3 = color_new(0.43f, 0.21f, 0.11f);

        assert(color_equal(c1, c2) == 1);
        assert(color_equal(c1, c3) == 0);

        log_msg("[Color Equal] All tests complete - pass");

        return 1;
}

int TST_ColorAdd()
{
        struct color c1 = color_new(0.8f, 0.1f, 0.005f);
        struct color c2 = color_new(0.25f, 0.333f, 0.5f);
        struct color c3 = color_new(1.05f, 0.433f, 0.505f);
        struct color c4 = color_new(1.85f, 0.533f, 0.51f);

        assert(color_equal(color_add(c1, c2), c3));
        assert(color_equal(color_add(c1, c3), c4));

        log_msg("[Color Add] All tests complete - pass!");

        return 1;
}

int TST_ColorSubtract()
{
        struct color c1 = color_new(0.8f, 0.1f, 0.5f);
        struct color c2 = color_new(0.25f, 0.333f, 0.005f);
        struct color c3 = color_new(0.55f, -0.233f, 0.495f);
        struct color c4 = color_new(0.25f, 0.333f, 0.005f);

        assert(color_equal(color_subtract(c1, c2), c3));
        assert(color_equal(color_subtract(c1, c3), c4));

        log_msg("[Color Subtract] All tests complete - pass!");

        return 1;
}

int TST_ColorScale()
{
        struct color c1 = color_new(0.2f, 0.4f, 0.8f);
        struct color c2 = color_new(0.4f, 0.8f, 1.6f);
        struct color c3 = color_new(0.5f, 1.0f, 2.0f);

        assert(color_equal(color_scale(c1, 2.0f), c2));
        assert(color_equal(color_scale(c1, 2.5f), c3));

        log_msg("[Color Scale] All tests complete - pass!");

        return 1;
}

int TST_ColorMultiply()
{
        struct color c1 = color_new(0.2f, 0.3f, 0.4f);
        struct color c2 = color_new(0.4f, 0.6f, 0.8f);
        struct color c3 = color_new(0.08f, 0.18f, 0.32f);
        struct color c4 = color_new(0.016f, 0.054f, 0.128f);

        assert(color_equal(color_multiply(c1, c2), c3));
        assert(color_equal(color_multiply(c1, c3), c4));

        log_msg("[Color Multiply] All tests complete - pass!");

        return 1;
}


int main()
{
        TST_ColorNewInt();
        TST_ColorEqual();
        TST_ColorAdd();
        TST_ColorSubtract();
        TST_ColorScale();
        TST_ColorMultiply();

        return 0;
}
