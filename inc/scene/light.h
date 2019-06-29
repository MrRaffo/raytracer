#ifndef __light_h__
#define __light_h__

#include <geometry/tuple.h>
#include <graphics/color.h>
#include <scene/material.h>

/* a point light with position and intensity */
struct p_light {
        struct tuple position;
        struct color intensity;
};

/* create a point light with given position and color */
const struct p_light p_light_new(struct tuple position, struct color intensity);

/* returns 1 if 2 given lights are equal, 0 otherwise */
const int p_light_equal(struct p_light l1, struct p_light l2);

const struct color light_phong(struct material m, struct p_light l,
                        struct tuple p,  struct tuple eye_v, struct tuple obj_n);

#endif // __light_h__
