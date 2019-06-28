
#include <stdio.h>
#include <assert.h>

#include <scene/light.h>
#include <geometry/tuple.h>
#include <graphics/color.h>

#include <util/mem.h>
#include <util/log.h>

TST_PLightNew()
{
        struct tuple p = tuple_point(0.0, 0.0, 0.0);
        struct color c = color_new(1.0, 1.0, 1.0);

        struct p_light l = p_light_new(p, c);

        assert(tuple_equal(l.position, p) == 1);
        assert(color_equal(l.intensity, c) == 1);

        struct p_light l2 = p_light_new(p, c);

        assert(p_light_equal(l, l2) == 1);

        log_msg("[P_Light New] Complete, all tests pass!");

        return 1;
}

int main()
{
        TST_PLightNew();

        mem_free_all();

        return 0;
}
