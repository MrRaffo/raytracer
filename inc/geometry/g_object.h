#ifndef __g_object_h__
#define __g_object_h__

/*
 * GEOMETRY or GRAPHICAL OBJECT
 * Will hold a catch-all struct to cover all primitive objects and materials a
 * ray can hit
 */

#include <geometry/sphere.h>

enum shape_type {
        SHAPE_ORIGIN = 0,           // Special type for the start of a ray
        SHAPE_SPHERE,
        NUM_SHAPES
};

// a graphical or geometric object
struct g_object {
        enum shape_type type;
};

/* create a sphere object, used for testing functions */
struct g_object *test_sphere();

#endif // __g_object_h__
