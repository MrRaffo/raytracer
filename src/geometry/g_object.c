#include <stdio.h>

#include <geometry/g_object.h>
#include <geometry/matrix.h>
#include <scene/material.h>

#include <util/mem.h>
#include <util/log.h>

/* OPERATIONS */

/* create a generic object for testing with no defined shape */
struct g_object *test_object()
{
        struct g_object *obj = (struct g_object *)mem_alloc(sizeof(struct g_object));
        obj->type = SHAPE_UNASSIGNED;
        obj->material = test_material();
        obj->transform = matrix_identity(4);
        obj->inverse_transform = matrix_identity(4);
        obj->transpose_inverse = matrix_identity(4);
        
        return obj;
}

/* set the objects transform and inverse matrix */
void object_transform(struct g_object *shape, struct matrix m)
{
        if (shape->transform.matrix != NULL) {
                mem_free(shape->transform.matrix);
                mem_free(shape->inverse_transform.matrix);
        }

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
                case SHAPE_PLANE:
                        return plane_normal_at(obj, point);
                        break;
                case SHAPE_SPHERE:
                        return sphere_normal_at(obj, point);
                        break;
                case SHAPE_UNASSIGNED:
                        log_wrn("Invalid object type: UNASSIGNED");
                        return tuple_zero();
                        break;
                default:
                        return tuple_zero();
                        log_wrn("Unrecognised object type");
        }

        return tuple_zero();
}

/* assign material properties to an object */
void object_set_material(struct g_object *obj, const struct material m)
{
        obj->material = m;
}

/* return 1 if objects are identical */
int object_equal(struct g_object *obj1, struct g_object *obj2)
{
        return (obj1->type == obj2->type &&
                material_equal(obj1->material, obj2->material) &&
                matrix_equal(obj1->transform, obj2->transform));
}

/* PRIMITIVES */

/* SPHERE */

/* create a sphere object, used for testing functions */
struct g_object *test_sphere()
{
        struct material material = test_material();
        struct matrix transform = matrix_identity(4);
        struct matrix inverse_transform = matrix_identity(4);
        struct matrix transpose_inverse = matrix_identity(4);
        struct g_object *sphere = (struct g_object *)mem_alloc(sizeof(struct g_object));
       
        sphere->type = SHAPE_SPHERE;
        sphere->material = material;
        object_transform(sphere, transform);
        //sphere->inverse_transform = inverse_transform;
        //sphere->transpose_inverse = transpose_inverse;

        return sphere;
}

/* create a sphere with given properties */
struct g_object *sphere(struct material material, struct matrix matrix)
{
        struct g_object *sphere = (struct g_object *)mem_alloc(sizeof(struct g_object));
        sphere->material = material;
        object_transform(sphere, matrix);
        sphere->type = SHAPE_SPHERE;

        return sphere;
}

/* get the normal at the point the ray hits the sphere */
const struct tuple sphere_normal_at(struct g_object *obj, const struct tuple point)
{
        struct tuple obj_point = matrix_transform(obj->inverse_transform, point);
        struct tuple obj_normal = tuple_subtract(obj_point, tuple_point(0.0, 0.0, 0.0));
        struct tuple world_normal = matrix_transform(obj->transpose_inverse, obj_normal);
        world_normal.w = 0.0;   // ensure it's treated as a vector

        return vector_normal(world_normal);
}

/* PLANE */

/* create a plane object for testing functions */
struct g_object *test_plane()
{
        struct g_object *plane = (struct g_object *)mem_alloc(sizeof(struct g_object));
        plane->type = SHAPE_PLANE;

        object_transform(plane, matrix_identity(4));

        return plane;
}

/* returns a normal vector pointing along positive y axis: (0.0, 1.0, 0.0, 0.0) */
const struct tuple plane_normal_at(struct g_object *obj, const struct tuple point)
{
        return tuple_vector(0.0, 1.0, 0.0);
}

