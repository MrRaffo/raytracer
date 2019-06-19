#ifndef __GOBJECT_H__
#define __GOBJECT_H__

/*
 * GEOMETRY or GRAPHICAL OBJECT
 * Will hold a catch-all struct to cover all primitive objects and materials a
 * ray can hit
 */

#include <geometry/sphere.h>

enum shape_type {
        SHAPE_ORIGIN,           // Special type for the start of a ray
        SHAPE_SPHERE            
};

// a graphical or geometric object
struct g_object {
        enum shape_type type;
};

#endif // __GOBJECT_H__
