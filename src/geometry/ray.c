#include <stdio.h>
#include <math.h>

#include <geometry/ray.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>
#include <geometry/g_object.h>
#include <geometry/intersection.h>

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
struct tuple ray_position(const struct ray r, const double t)
{
        struct tuple pos = tuple_add(r.org, tuple_scale(r.dir, t));
        return pos;
}

/* counts up to two intersections for a sphere and returns an intersect struct
 * which contains info about how many intersections were found and info about
 * them
 */
int _sphere_intersect(const struct ray r, struct g_object *s, struct i_list *list)
{
        // (o-c): center of sphere is always at (0,0,0)
        struct tuple v = {r.org.x, r.org.y, r.org.z, 0.0f};
        double ldotv = vector_dot(r.dir, v);
        double sq = ldotv * ldotv;
        double mag = vector_magnitude(v);
        double magsq = mag * mag;

        if ((sq - (magsq - 1.0f)) < 0.0f) {
                return 0;
        } else if (double_equal(sq - (magsq - 1.0f), 0.0f) == 1) {
                double t = -1.0f * ldotv;
                struct intersection *i = intersection_new(t, s);
                add_intersection(list, i);
                return 1;
        }

        double root = sqrt(sq - (magsq - 1.0f));
        double t1 = -1.0f * ldotv - root;
        double t2 = -1.0f * ldotv + root;

        struct intersection *i1 = intersection_new(t1, s);
        add_intersection(list, i1);
        
        struct intersection *i2 = intersection_new(t2, s);
        add_intersection(list, i2);        

        return 2;
}

/* checks for intersections between the ray and object, returns number found */
int ray_intersect(const struct ray r, struct g_object *obj, struct i_list *list)
{
        // need to transform the ray by the inverse of the objects transform
        // matrix, as this is easier than translating the object itself
        struct ray t_ray = ray_transform(r, matrix_inverse(obj->transform));

        switch (obj->type) {
        case SHAPE_SPHERE:
                return _sphere_intersect(t_ray, obj, list);
                break;
        default:
                break;
        }

        return 0;
}

/* returns the ray that results in the current ray being transformed by the matrix */
struct ray ray_transform(const struct ray r, struct matrix m)
{
        struct tuple org = matrix_transform(m, r.org);
        struct tuple dir = matrix_transform(m, r.dir);
        struct ray res = {org, dir};
        return res;
}


