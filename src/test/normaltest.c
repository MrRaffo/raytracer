/*
 * Checks surface normals are working as intended
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <geometry/g_object.h>
#include <geometry/tuple.h>

#include <util/log.h>
#include <util/mem.h>

int TST_SphereNormal()
{
        struct g_object *s = test_sphere();
        
        // normal at point on x axis:
        struct tuple expected_n = tuple_vector(1.0, 0.0, 0.0);
        struct tuple n = object_normal_at(s, tuple_point(1.0, 0.0, 0.0));
        assert(tuple_equal(n, expected_n) == 1);

        // normal at point on the y axis
        expected_n = tuple_vector(0.0, 1.0, 0.0);
        n = object_normal_at(s, tuple_point(0.0, 1.0, 0.0));
        assert(tuple_equal(n, expected_n) == 1);

        // normal at point on the z axis
        expected_n = tuple_vector(0.0, 0.0, 1.0);
        n = object_normal_at(s, tuple_point(0.0, 0.0, 1.0));
        assert(tuple_equal(n, expected_n) == 1);

        // normal at a nonaxial point
        double ax = sqrt(3.0)/3.0;
        expected_n = tuple_vector(ax, ax, ax);
        n = object_normal_at(s, tuple_point(ax, ax, ax));
        assert(tuple_equal(n, expected_n) == 1);

        log_msg("[Sphere Normal] Complete, all tests pass!");
        return 1;
}

// ensure sphere normal is of length 1
int TST_SphereNormalNormalized()
{
        // normal at a nonaxial point
        struct g_object *s = test_sphere();

        double ax = sqrt(3.0)/3.0;
        struct tuple expected_n = tuple_vector(ax, ax, ax);
        struct tuple n = object_normal_at(s, tuple_point(ax, ax, ax));
        assert(tuple_equal(n, expected_n) == 1);
        assert(tuple_equal(n, vector_normal(n)) == 1);

        log_msg("[Normalized] Complete, all tests pass!");

        return 1;
}

// ensure normal is correct for transformed spheres 
int TST_SphereTransformedNormal()
{
        struct g_object *s = test_sphere();
        struct matrix m = matrix_translate(0.0, 1.0, 0.0);

        // translated sphere
        object_transform(s, m);
        struct tuple n = object_normal_at(s, tuple_point(0.0, 1.70711, -0.70711));
        assert(tuple_equal(n, tuple_vector(0.0, 0.70711, -0.70711)) == 1);

        // scaled and rotated sphere
        struct matrix scale = matrix_scale(1.0, 0.5, 1.0);
        struct matrix rotate = matrix_rotate_z(M_PI/5.0);
        m = matrix_multiply(scale, rotate);
        object_transform(s, m);

        n = object_normal_at(s, tuple_point(0.0, sqrt(2.0)/2.0, -sqrt(2.0)/2.0));
        assert(tuple_equal(n, tuple_vector(0.0, 0.97014, -0.24254)) == 1);

        log_msg("[Transformed Normal] Complete, all tests pass!");
        return 1;
}

TST_PlaneNormal()
{
        /* plane local normal is always 'up' */
        struct g_object *plane = test_plane();
        
        struct tuple normal = object_normal_at(plane, tuple_point(0.0, 0.0, 0.0));
        assert(tuple_equal(normal, tuple_vector(0.0, 1.0, 0.0)) == 1);

        normal = object_normal_at(plane, tuple_point(10.0, 0.0, -10.0));
        assert(tuple_equal(normal, tuple_vector(0.0, 1.0, 0.0)) == 1);

        normal = object_normal_at(plane, tuple_point(-5.0, 0.0, 150.0));
        assert(tuple_equal(normal, tuple_vector(0.0, 1.0, 0.0)) == 1);

        log_msg("[Plane Normal] Complete, all tests pass!");

        return 1;
}

int main()
{
        TST_SphereNormal();
        TST_SphereNormalNormalized();
        TST_SphereTransformedNormal();

        TST_PlaneNormal();

        return 0;
}
