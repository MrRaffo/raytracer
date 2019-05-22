#ifndef __gmaths_h__
#define __gmaths_h__

#define GEO_EPSILON 0.00001f     // used as a threshold for comparing float

/* 
 * Compare two floats, return 1 if they are equal (with EPSILON of each other),
 * 0 otherwise
 */
const int GEO_Equal(const float val1, const float val2);

#endif // __gmaths_h__
