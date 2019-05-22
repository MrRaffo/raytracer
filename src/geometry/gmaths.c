#include <stdio.h>
#include <math.h>

#include <geometry/gmaths.h>

/* 
 * Compare two floats, return 1 if they are equal (with EPSILON of each other),
 * 0 otherwise
 */
const int GEO_Equal(const float val1, const float val2)
{
        return (fabs(val1 - val2)) < GEO_EPSILON ? 1 : 0;
}


