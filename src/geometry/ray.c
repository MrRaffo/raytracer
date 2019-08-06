#include <stdio.h>
#include <math.h>

#include <geometry/ray.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/g_maths.h>
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
        struct tuple sphere_to_ray = tuple_subtract(r.org, 
                                                    tuple_point(0.0,0.0,0.0));

        // this is a quadratic equation, the 'a', 'b' and 'c' components
        // are given thus:
        double a = vector_dot(r.dir, r.dir);
        double b = 2.0 * vector_dot(r.dir, sphere_to_ray);
        double c = vector_dot(sphere_to_ray, sphere_to_ray) - 1.0;

        // this is the squared part, if it is below zero there are no solutions
        // ie, no intersections, if it is zero there is one solution, the ray
        // just grazes the sphere at a tangent, and if it is positive there are
        // two solutions, the entry and exit points of the ray on the sphere
        double discriminant = (b * b) - (4.0 * a) * c;

        if (discriminant < 0.0) {
                return 0;
        }

        if (discriminant == 0.0) {
                double t = (-1.0 * b) / (2.0 * a);
                struct intersection *i1 = intersection_new(t, s);
                add_intersection(list, i1);
                return 1;
        }

        double t1, t2;
        double d_root = sqrt(discriminant);

        t1 = (-1.0 * b - d_root) / (2.0 * a);
        t2 = (-1.0 * b + d_root) / (2.0 * a);

        struct intersection *i1 = intersection_new(t1, s);
        add_intersection(list, i1);
        
        struct intersection *i2 = intersection_new(t2, s);
        add_intersection(list, i2);        

        return 2;
}

/* find the point at which a ray intersects a plane */
int _plane_intersect(const struct ray r, struct g_object *plane, struct i_list *list)
{
        /* any ray which doesn't move in y-axis is parallel or coplanar */
        if (fabs(r.dir.y) < EPSILON) {
                return 0;
        }

        double t = -r.org.y / r.dir.y;
        struct intersection *i = intersection_new(t, plane);
        add_intersection(list, i);

        return 1;
}

/* checks for intersections between the ray and object, returns number found */
int ray_intersect(const struct ray r, struct g_object *obj, struct i_list *list)
{
        // need to transform the ray by the inverse of the objects transform
        // matrix, as this is easier than translating the object itself
        struct ray t_ray = ray_transform(r, obj->inverse_transform);

        switch (obj->type) {
        case SHAPE_SPHERE:
                return _sphere_intersect(t_ray, obj, list);
                break;
        case SHAPE_PLANE:
                return _plane_intersect(t_ray, obj, list);
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


