#include <stdio.h>

#include <geometry/sphere.h>
#include <geometry/tuple.h>

#include <util/log.h>

/* returns a unit sphere, centered on the origin */
const struct sphere sphere_unit()
{
        struct sphere s = {tuple_point(0.0f, 0.0f, 0.0f), 1.0f};
        return s;
}

/* returns a sphere to the given specifications */
const struct sphere sphere_new(const struct tuple pos, const double radius)
{
        struct sphere s = {pos, radius};
        return s;
}



