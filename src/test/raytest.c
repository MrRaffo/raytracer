#include <stdio.h>
#include <geometry/ray.h>
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

int main()
{
        TST_RayNew();
        TST_RayPosition();

        mem_free_all();

        return 0;
}
