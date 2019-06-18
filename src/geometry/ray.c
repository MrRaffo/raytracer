#include <stdio.h>
#include <math.h>

#include <geometry/ray.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>

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

/* populates passed intersection struct with intersection
 * points if possible and returns number of intersections
 * ray must be normalised
 */
int ray_sphere_intersect(const struct ray r, const struct sphere s, struct intersect *i)
{
        // (o-c): center of sphere is always at (0,0,0)
        struct tuple v = {r.org.x, r.org.y, r.org.z, 0.0f};
        double ldotv = vector_dot(r.dir, v);
        double sq = ldotv * ldotv;
        double mag = vector_magnitude(v);
        double magsq = mag * mag;

        if ((sq - (magsq - 1.0f)) < 0.0f) {
                i->found = 0;
                return 0;
        } else if (double_equal(sq - (magsq - 1.0f), 0.0f) == 1) {
                i->found = 1;
                i->ione = i->itwo = -1.0f * ldotv;
                return 1;
        }

        i->found = 2;
        double root = sqrt(sq - (magsq - 1.0f));
        i->ione = -1.0f * ldotv - root;
        i->itwo = -1.0f * ldotv + root;
        return 2;
}

