#include <stdio.h>
#include <geometry/g_maths.h>
#include <util/log.h>
#include <assert.h>


int TST_Equal()
{
        double val1 = 2.52365;
        double val2 = 3.3569958123;
        double val3 = 3.3569923;

        assert(double_equal(val1, val2) == 0);
        assert(double_equal(val1, val3) == 0);
        assert(double_equal(val2, val3) == 1);

        log_msg("[Equality (double)] All tests complete - pass!");

        return 1;
}

int main()
{
        TST_Equal();

        return 0;
}
