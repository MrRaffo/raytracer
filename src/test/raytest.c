#include <stdio.h>
#include <geometry/ray.h>
#include <geometry/sphere.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>

#include <util/log.h>
#include <util/mem.h>
#include <assert.h>

int TST_RayNew()
{
        struct tuple t = tuple_point(1.0f, 2.0f, 3.0f);
        struct tuple v = tuple_vector(2.0f, 4.0f, 6.0f);
        struct ray r = ray_new(t, v);

        assert(tuple_equal(r.org, t) == 1);
        assert(tuple_equal(r.dir, v) == 1);

        fprintf(stdout, "[RAY NEW] Complete, all tests pass!\n");
        return 1;
}

int TST_RayPosition()
{
        struct tuple start = tuple_point(2.0f, 3.0f, 4.0f); 
        struct tuple dir = tuple_vector(1.0f, 0.0f, 0.0f); 

        struct tuple p1 = tuple_point(2.0f, 3.0f, 4.0f);
        struct tuple p2 = tuple_point(3.0f, 3.0f, 4.0f);
        struct tuple p3 = tuple_point(1.0f, 3.0f, 4.0f);
        struct tuple p4 = tuple_point(4.5f, 3.0f, 4.0f);

       struct ray r = ray_new(start, dir);

        assert(tuple_equal(ray_position(r, 0.0f), p1) == 1);
        assert(tuple_equal(ray_position(r, 1.0f), p2) == 1);
        assert(tuple_equal(ray_position(r, -1.0f), p3) == 1);
        assert(tuple_equal(ray_position(r, 2.5f), p4) == 1);

        fprintf(stdout, "[RAY POSITION] Complete, all tests pass!\n");
        return 1;
}

int TST_RaySphereIntersect()
{
        struct tuple o = tuple_point(0.0f, 0.0f, -5.0f);
        struct tuple d = tuple_vector(0.0f, 0.0f, 1.0f);
        struct ray r = ray_new(o, d);
        struct sphere s = sphere_unit();

        struct intersect i;
        ray_sphere_intersect(r, s, &i);
        
        // intersect at 2 points
        assert(i.found == 2);
        assert(double_equal(i.ione, 4.0f) == 1);
        assert(double_equal(i.itwo, 6.0f) == 1);

        // intersect at one point
        o = tuple_point(0.0f, 1.0f, -5.0f);
        r = ray_new(o, d);
        ray_sphere_intersect(r, s, &i);

        assert(i.found == 1);
        assert(double_equal(i.ione, 5.0f) == 1);
        assert(double_equal(i.itwo, 5.0f) == 1);

        // never intersects
        o = tuple_point(0.0f, 2.0f, -5.0f);
        r = ray_new(o, d);
        ray_sphere_intersect(r, s, &i);

        assert(i.found == 0);

        // ray origin inside sphere
        o = tuple_point(0.0f, 0.0f, 0.0f);
        r = ray_new(o, d);
        ray_sphere_intersect(r, s, &i);

        assert(i.found == 2);
        assert(double_equal(i.ione, -1.0f) == 1);
        assert(double_equal(i.itwo, 1.0f) == 1);

        // ray origin beyond sphere (negative distance)
        o = tuple_point(0.0f, 0.0f, 5.0f);
        r = ray_new(o, d);
        ray_sphere_intersect(r, s, &i);

        assert(i.found == 2);
        assert(double_equal(i.ione, -6.0f) == 1);
        assert(double_equal(i.itwo, -4.0f) == 1);

        fprintf(stdout, "[RAY SPHERE INTERSECT] Complete, all tests pass!\n");

        return 1;
}

int main()
{
        TST_RayNew();
        TST_RayPosition();
        TST_RaySphereIntersect();

        mem_free_all();

        return 0;
}
