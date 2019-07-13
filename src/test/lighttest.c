
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <scene/light.h>
#include <geometry/tuple.h>
#include <graphics/color.h>

#include <util/mem.h>
#include <util/log.h>

int TST_PLightNew()
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

int TST_Phong()
{
        struct material m = test_material();
        struct tuple p = tuple_point(0.0, 0.0, 0.0);

        // eye between light source and object, full intensity
        struct tuple eye_v = tuple_vector(0.0, 0.0, -1.0);
        struct tuple obj_n = tuple_vector(0.0, 0.0, -1.0);
        struct p_light light = p_light_new(tuple_point(0.0, 0.0, -10.0), color_new(1.0, 1.0, 1.0));
        struct color result = light_phong(m, light, p, eye_v, obj_n, 0);
        
        assert(color_equal(result, color_new(1.9, 1.9, 1.9)) == 1);

        // eye at 45 degree to surface normal
        eye_v = tuple_vector(0.0, sqrt(2.0)/2.0, -sqrt(2.0)/2.0);
        result = light_phong(m, light, p, eye_v, obj_n, 0);

        assert(color_equal(result, color_new(1.0, 1.0, 1.0)) == 1);

        // light 45 degrees from normal, eye at 0
        eye_v = tuple_vector(0.0, 0.0, -1.0);
        light = p_light_new(tuple_point(0.0, 10.0, -10.0), color_new(1.0, 1.0, 1.0));
        result = light_phong(m, light, p, eye_v, obj_n, 0);

        assert(color_equal(result, color_new(0.7364, 0.7364, 0.7364)) == 1);

        // light 45 degrees above, eye 45 degrees below
        eye_v = tuple_vector(0.0, -sqrt(2.0)/2.0, -sqrt(2.0)/2.0);
        result = light_phong(m, light, p, eye_v, obj_n, 0);

        assert(color_equal(result, color_new(1.6364, 1.6364, 1.6364)) == 1);

        // light on other side of object to eye
        light = p_light_new(tuple_point(0.0, 0.0, 10.0), color_new(1.0, 1.0, 1.0));
        eye_v = tuple_vector(0.0, 0.0, -1.0);
        result = light_phong(m, light, p, eye_v, obj_n, 0);

        // only ambient shows
        assert(color_equal(result, color_new(0.1, 0.1, 0.1)) == 1);

        log_msg("[Phong Lighting] Complete, all tests pass!");

        return 1;
}

int TST_InShadow()
{
        struct material m = test_material();
        struct tuple pos = tuple_point(0.0, 0.0, 0.0);
        
        struct tuple eye_v = tuple_vector(0.0, 0.0, -1.0);
        struct tuple nor_v = tuple_vector(0.0, 0.0, -1.0);
        struct p_light l = p_light_new(tuple_point(0.0, 0.0, -10.0),
                                       color_new(1.0, 1.0, 1.0));
        int in_shadow = 1;

        struct color result = light_phong(m, l, pos, eye_v, nor_v, in_shadow);
        assert(color_equal(result, color_new(0.1, 0.1, 0.1)) == 1);

        log_msg("[In Shadow] Complete, all tests pass!");
        
        return 1;
}

int main()
{
        TST_PLightNew();
        TST_Phong();
        TST_InShadow();

        mem_free_all();

        return 0;
}
