#include <stdio.h>

#include <geometry/g_object.h>
#include <geometry/sphere.h>

/* create a sphere object, used for testing functions */
struct g_object *test_sphere()
{
        struct g_object *s = (struct g_object *)mem_alloc(sizeof(struct g_object));
        s->type == SHAPE_SPHERE;
        return s;
}
