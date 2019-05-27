#include <stdio.h>
#include <graphics/color.h>
#include <geometry/gmaths.h>    // for float_equal

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

        fprintf(stdout, "[Color NewInt] All tests complete - pass!\n");

        return 1;
}

int main()
{
        TST_ColorNewInt();

        return 0;
}
