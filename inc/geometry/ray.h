#ifndef __ray_h__
#define __ray_h__

/*
 * A ray type for the raytracer
 */

#include <geometry/tuple.h>
#include <geometry/sphere.h>

struct ray {
        struct tuple org;       // origin
        struct tuple dir;       // direction
};

/* this struct records the distance along a ray from its
 * origin to the first and second intersections of a 
 * convex volume, if there is only one intersection, both
 * values will be equal to the distance of the only
 * intersection
 */
struct intersect {
        int found;
        double ione;
        double itwo;
};

/* records the distance along a ray an intersection is found along with the
 * object being intersected */
struct intersection {
        double t;
        union object;
};

/* CREATION */

/* Create a ray with given origin and direction tuples */
struct ray ray_new(const struct tuple origin, const struct tuple direction);

/* return a character string representing the ray */
char *ray_to_string(const struct ray r);

/* return the position after travelling distance t */
struct tuple ray_position(const struct ray r, const double t);

/* populates passed intersection struct with intersection
 * points if possible and returns number of intersections
 */
int ray_sphere_intersect(const struct ray r, const struct sphere s, struct intersect *i);

#endif // __ray_h__
