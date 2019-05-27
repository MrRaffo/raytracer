#include <stdio.h>
#include <geometry/gmaths.h>
#include <assert.h>


int TST_Equal()
{
        float val1 = 2.52365;
        float val2 = 3.3569958123;
        float val3 = 3.3569923;

        assert(float_equal(val1, val2) == 0);
        assert(float_equal(val1, val3) == 0);
        assert(float_equal(val2, val3) == 1);

        fprintf(stdout, "[Equality (float)] All tests complete - pass!\n");

        return 1;
}

int main()
{
        TST_Equal();

        return 0;
}
