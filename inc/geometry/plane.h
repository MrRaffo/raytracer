#ifndef __sphere_h__
#define __sphere_h__

#include <geometry/tuple.h>

struct sphere {
        struct tuple pos;
        double radius;
};

/* CREATION */

/* returns a unit sphere, centered on the origin */
const struct sphere sphere_unit();

/* returns a sphere to the given specifications */
const struct sphere sphere_new(const struct tuple pos, const double radius);


#endif // __sphere_h__
