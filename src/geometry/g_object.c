#include <stdio.h>

#include <geometry/g_object.h>
#include <geometry/sphere.h>
#include <geometry/matrix.h>

#include <util/mem.h>

/* create a sphere object, used for testing functions */
struct g_object *test_sphere()
{
        struct g_object *s = (struct g_object *)mem_alloc(sizeof(struct g_object));
        s->type = SHAPE_SPHERE;
        s->transform = matrix_identity(4);
        return s;
}

/* set the objects transform matrix */
void object_transform(struct g_object *shape, struct matrix m)
{
        // TODO - might be nice to free memory from previous matrix here
        shape->transform = m;
}
