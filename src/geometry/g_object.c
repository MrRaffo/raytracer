#include <stdio.h>

#include <geometry/g_object.h>
#include <geometry/sphere.h>
#include <geometry/matrix.h>

#include <util/mem.h>
#include <util/log.h>

/* create a sphere object, used for testing functions */
struct g_object *test_sphere()
{
        struct g_object *s = (struct g_object *)mem_alloc(sizeof(struct g_object));
        s->type = SHAPE_SPHERE;
        s->transform = matrix_identity(4);
        s->inverse_transform = matrix_identity(4);
        s->transpose_inverse = matrix_identity(4);
        return s;
}

/* set the objects transform and inverse matrix */
void object_transform(struct g_object *shape, struct matrix m)
{
        mem_free(shape->transform.matrix);
        mem_free(shape->inverse_transform.matrix);

        shape->transform = m;
        // saving the inverse here prevents needing every ray to calculate it
        shape->inverse_transform = matrix_inverse(m);
        // this is useful for translating world->object space for surface normals
        shape->transpose_inverse = matrix_transpose(shape->inverse_transform);
}

/* calculate the surface normal on an object at the given point */
const struct tuple object_normal_at(struct g_object *obj, struct tuple point)
{
        switch(obj->type) {
                case SHAPE_ORIGIN:
                        log_err("Invalid object type: ORIGIN");
                        return tuple_zero();
                        break;
                case SHAPE_SPHERE:
                        return sphere_normal_at(obj, point);
                        break;
                default:
                        return tuple_zero();
                        log_wrn("Unrecognised object type");
        }

        return tuple_zero();
}

const struct tuple sphere_normal_at(struct g_object *obj, const struct tuple point)
{
        struct tuple obj_point = matrix_transform(obj->inverse_transform, point);
        struct tuple obj_normal = tuple_subtract(obj_point, tuple_point(0.0, 0.0, 0.0));
        struct tuple world_normal = matrix_transform(obj->transpose_inverse, obj_normal);
        world_normal.w = 0.0;   // ensure it's treated as a vector

        return vector_normal(world_normal);
}
