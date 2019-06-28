
#include <stdio.h>

#include <scene/light.h>
#include <geometry/tuple.h>
#include <graphics/color.h>

#include <util/mem.h>
#include <util/log.h>

/* create a point light with given position and color */
const struct p_light p_light_new(struct tuple position, struct color intensity)
{
        struct p_light l = {position, intensity};
        return l;
}

/* returns 1 if 2 given lights are equal, 0 otherwise */
const int p_light_equal(struct p_light l1, struct p_light l2)
{
        return (tuple_equal(l1.position, l2.position) && 
                        color_equal(l1.intensity, l2.intensity));
}


