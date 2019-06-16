#include <stdio.h>

#include <geometry/ray.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>

#include <util/log.h>
#include <util/mem.h>

/* CREATION */

/* Create a ray with given origin and direction tuples */
struct ray ray_new(const struct tuple origin, const struct tuple direction)
{
        struct ray r = {origin, direction};
        return r;
}

/* return a character string representing the ray */
char *ray_to_string(const struct ray r)
{
        return NULL;
}

/* return the position after travelling distance t */
struct tuple ray_position(const struct ray r, const float t)
{
        struct tuple pos = tuple_add(r.org, tuple_scale(r.dir, t));
        return pos;
}
