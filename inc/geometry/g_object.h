#ifndef __g_object_h__
#define __g_object_h__

/*
 * GEOMETRY or GRAPHICAL OBJECT
 * Will hold a catch-all struct to cover all primitive objects and materials a
 * ray can hit
 */

#include <geometry/matrix.h>
#include <scene/material.h>

enum shape_type {
        SHAPE_ORIGIN = 0,       // Special type for the start of a ray
        SHAPE_PLANE,
        SHAPE_SPHERE,
        SHAPE_UNASSIGNED,       // a default for testing purposes
        NUM_SHAPES
};

// a graphical or geometric object
struct g_object {
        enum shape_type type;
        struct material material;
        struct matrix transform;
        struct matrix inverse_transform;        // for ray intersections
        struct matrix transpose_inverse;        // for surface normals
};

/* OPERATIONS */

/* create a generic object for testing with no defined shape */
struct g_object *test_object();

/* set the objects transform and inverse matrix */
void object_transform(struct g_object *shape, struct matrix m);

/* calculate the surface normal on an object at the given point */
const struct tuple object_normal_at(struct g_object *obj, struct tuple point);

/* assign material properties to an object */
void object_set_material(struct g_object *obj, const struct material m);

/* return 1 if objects are identical */
int object_equal(struct g_object *obj1, struct g_object *obj2);

/* PRIMITIVES */

/* SPHERE */

/* create a sphere object, used for testing functions */
struct g_object *test_sphere();

/* create a sphere with given properties */
struct g_object *sphere(struct material material, struct matrix matrix);

/* returns the normal at the point the sphere was hit */
const struct tuple sphere_normal_at(struct g_object *obj, const struct tuple point);

/* PLANE */

/* create a plane object for testing functions */
struct g_object *test_plane();

/* returns a normal vector pointing along positive y axis: (0.0, 1.0, 0.0, 0.0) */
const struct tuple plane_normal_at(struct g_object *obj, const struct tuple point);

#endif // __g_object_h__
