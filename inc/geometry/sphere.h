#ifndef __sphere_h__
#define __sphere_h__

#include <geometry/tuple.h>

struct g_object;

/* OPERATIONS */

/* returns the normal at the point the sphere was hit */
const struct tuple sphere_normal_at(struct g_object *obj, const struct tuple point);

#endif // __sphere_h__
