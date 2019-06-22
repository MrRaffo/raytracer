#ifndef __ray_h__
#define __ray_h__

/*
 * A ray type for the raytracer
 */

#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/g_object.h>
#include <geometry/intersection.h>

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
struct tuple ray_position(const struct ray r, const double t);

/* counts up to two intersections for a sphere and returns an intersect struct
 * which contains info about how many intersections were found and info about
 * them
 */
int _sphere_intersect(const struct ray r, struct g_object *s, struct i_list *list);

/* checks for intersections between the ray and object, returns number found */
int ray_intersect(const struct ray r, struct g_object *obj, struct i_list *list);

/* returns the ray that results in the current ray being transformed by the matrix */
struct ray ray_transform(const struct ray r, struct matrix m);

#endif // __ray_h__
