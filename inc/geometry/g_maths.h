#ifndef __g_maths_h__
#define __g_maths_h__

#define EPSILON 0.00001     // used as a threshold for comparing double

/* 
 * Compare two doubles, return 1 if they are equal (with EPSILON of each other),
 * 0 otherwise
 */
const int double_equal(const double val1, const double val2);

#endif // __g_maths_h__
