#include <stdio.h>
#include <math.h>

#include <geometry/g_maths.h>

/* 
 * Compare two doubles, return 1 if they are equal (with EPSILON of each other),
 * 0 otherwise
 */
const int double_equal(const double val1, const double val2)
{
        return (fabs(val1 - val2)) < EPSILON ? 1 : 0;
}


