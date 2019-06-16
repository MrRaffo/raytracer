#include <stdio.h>
#include <geometry/sphere.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>

#include <util/log.h>
#include <util/mem.h>
#include <assert.h>

int TST_SphereUnit()
{
        struct tuple t = tuple_point(0.0f, 0.0f, 0.0f);
        struct sphere s = sphere_unit();

        assert(tuple_equal(s.pos, t) == 1);
        assert(float_equal(s.radius, 1.0f) == 1);

        fprintf(stdout, "[SPHERE UNIT] Complete, all tests pass!\n");
        return 1;
}

int TST_SphereNew()
{
        struct tuple pos = tuple_point(1.0f, 2.0f, 3.0f);
        struct sphere s = sphere_new(pos, 5.0f);

        assert(tuple_equal(s.pos, pos) == 1);
        assert(float_equal(s.radius, 5.0f) == 1);

        fprintf(stdout, "[SPHERE NEW] Complete, all tests pass!\n");
        return 1;
}

int main()
{
        TST_SphereUnit();
        TST_SphereNew();

        mem_free_all();

        return 0;
}
