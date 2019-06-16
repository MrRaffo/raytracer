#ifndef __ray_h__
#define __ray_h__

/*
 * A ray type for the raytracer
 */

#include <geometry/tuple.h>

struct ray {
        struct tuple org;       // origin
        struct tuple dir;       // direction
};

/* CREATION */

/* Create a ray with given origin and direction tuples */
struct ray ray_new(const struct tuple origin, const struct tuple direction);

/* return a character string representing the ray */
char *ray_to_string(const struct ray r);

/* return the position after travelling distance t */
struct tuple ray_position(const struct ray r, const float t);

#endif // __ray_h__
