#ifndef __g_object_h__
#define __g_object_h__

/*
 * GEOMETRY or GRAPHICAL OBJECT
 * Will hold a catch-all struct to cover all primitive objects and materials a
 * ray can hit
 */

#include <geometry/sphere.h>
#include <geometry/matrix.h>

enum shape_type {
        SHAPE_ORIGIN = 0,           // Special type for the start of a ray
        SHAPE_SPHERE,
        NUM_SHAPES
};

// a graphical or geometric object
struct g_object {
        enum shape_type type;
        struct matrix transform;
        struct matrix inverse_transform;
};

/* create a sphere object, used for testing functions */
struct g_object *test_sphere();

/* set the objects transform and inverse matrix */
void object_transform(struct g_object *shape, struct matrix m);

#endif // __g_object_h__
