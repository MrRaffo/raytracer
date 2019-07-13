#include <stdio.h>
#include <math.h>
#include <assert.h>

#include <scene/world.h>
#include <scene/light.h>
#include <scene/material.h>
#include <geometry/g_object.h>
#include <geometry/intersection.h>
#include <geometry/ray.h>
#include <graphics/color.h>

#include <util/log.h>
#include <util/mem.h>

int TST_WorldCreate()
{
        struct world *w = world_new();
        assert(w->objects == NULL);
        assert(w->lights == NULL);
        
        log_msg("[Test World Creation] Complete, all tests pass!");
        return 1;
}

int TST_TestWorld()
{
        struct world *test_w = test_world();

        struct p_light light = p_light_new(tuple_point(-10.0, 10.0, -10.0),
                                           color_new(1.0, 1.0, 1.0));
        struct material material = material_new(color_new(0.8, 1.0, 0.6),
                                                0.1, 0.7, 0.2, 200.0);
        struct matrix scale = matrix_scale(0.5, 0.5, 0.5);

        struct g_object *s1 = test_sphere();
        object_set_material(s1, material);
        struct g_object *s2 = test_sphere();
        object_transform(s2, scale);

        assert(object_equal(test_w->objects->object, s1) == 1);
        assert(world_has_object(test_w, s2) == 1);
        assert(world_has_light(test_w, light) == 1);

        log_msg("[Test World] Complete, all tests pass!");

        return 1;
}

int TST_WorldRayIntersect()
{
        struct world *test_w = test_world();
        struct ray ray = ray_new(tuple_point(0.0, 0.0, -5.0), 
                                  tuple_vector(0.0, 0.0, 1.0));

        struct i_list *xs = i_list_new();

        int count = world_ray_intersections(test_w, ray, xs);

        assert(count == 4);
        assert(count == xs->count);
        assert(double_equal(get_intersection(xs, 0)->t, 4.0) == 1);
        assert(double_equal(get_intersection(xs, 1)->t, 4.5) == 1);
        assert(double_equal(get_intersection(xs, 2)->t, 5.5) == 1);
        assert(double_equal(get_intersection(xs, 3)->t, 6.0) == 1);

        log_msg("[Test Ray-World Intersect] Complete, all tests pass!");
        
        return 1;
}

int TST_WorldShade()
{
        struct world *test_w = test_world();
        struct ray r = ray_new(tuple_point(0.0, 0.0, -5.0), 
                               tuple_vector(0.0, 0.0, 1.0));
        
        struct w_obj_node *obj_n = test_w->objects;
        struct g_object *s = obj_n->object;
        struct intersection *i = intersection_new(4.0, s);
        struct i_comp comps = i_pre_compute(i, r);
        struct color col = world_shade_hit(test_w, comps);

        assert(color_equal(col, color_new(0.38066, 0.47583, 0.2855)) == 1);

        // shading an intersection from the inside
        struct w_light_node *light_n = test_w->lights;
        light_n->light.position = tuple_point(0.0, 0.25, 0.0);
        light_n->light.intensity = color_new(1.0, 1.0, 1.0);

        r = ray_new(tuple_point(0.0, 0.0, 0.0), tuple_vector(0.0, 0.0, 1.0));
        s = obj_n->next->object;
        i->t = 0.5;
        i->obj = s;
        comps = i_pre_compute(i, r);
        col = world_shade_hit(test_w, comps);

        assert(color_equal(col, color_new(0.90498, 0.90498, 0.90498)) == 1);

        log_msg("[Shade Hit] Complete, all tests pass!");
        return 1;
}

int TST_WorldColorAt()
{
        struct world *w = test_world();
        struct ray r = ray_new(tuple_point(0.0, 0.0, -5.0), 
                               tuple_vector(0.0, 1.0, 0.0));

        // ray misses objects
        struct color c = world_color_at(w, r);
        assert(color_equal(c, color_new(0.0, 0.0, 0.0)) == 1);

        r.dir = tuple_vector(0.0, 0.0, 1.0);
        struct color c2 = world_color_at(w, r);
        assert(color_equal(c2, color_new(0.38066, 0.47583, 0.2855)) == 1);

        // ray starts inside outer sphere and hits inner sphere
        w->objects->object->material.ambient = 1.0;
        w->objects->next->object->material.ambient = 1.0;

        r.org = tuple_point(0.0, 0.0, 0.75);
        r.dir = tuple_vector(0.0, 0.0, -1.0);

        struct color c3 = world_color_at(w, r);
        assert(color_equal(c3, w->objects->next->object->material.color) == 1);
        
        log_msg("[Color At] Complete, all tests pass!");

        return 1;
}

int TST_PointInShadow()
{
        struct world *w = test_world();
        struct tuple p = tuple_point(0.0, 10.0, 0.0);
        struct p_light l = w->lights->light;

        // nothing between point and light source
        assert(world_point_is_shadowed(w, l, p) == 0);

        // sphere between point and light
        p = tuple_point(10.0, -10.0, 10.0);
        assert(world_point_is_shadowed(w, l, p) == 1);

        // light between point and object
        p = tuple_point(-20.0, 20.0, -20.0);
        assert(world_point_is_shadowed(w, l, p) == 0);

        // point between light and object
        p = tuple_point(-2.0, 2.0, -2.0);
        assert(world_point_is_shadowed(w, l, p) == 0);

        log_msg("[Point in Shadow] Complete, all tests pass!");
        return 1;
}

int TST_ShadeHitInShadow()
{
        struct world *w = world_new();
        struct p_light l = p_light_new(tuple_point(0.0, 0.0, -10.0), 
                                     color_new(1.0, 1.0, 1.0));

        struct g_object *s1 = test_sphere();
        struct g_object *s2 = test_sphere();

        struct matrix s2transform = matrix_translate(0.0, 0.0, 10.0);
        object_transform(s2, s2transform);

        world_add_object(w, s1);
        world_add_object(w, s2);
        world_add_light(w, l);

        struct ray r = ray_new(tuple_point(0.0, 0.0, 5.0), 
                               tuple_vector(0.0, 0.0, 1.0));

        struct intersection *i = intersection_new(4.0, s2);
        struct i_comp comp = i_pre_compute(i, r);

        struct color c = world_shade_hit(w, comp);

        assert(color_equal(c, color_new(0.1, 0.1, 0.1)) == 1);

        log_msg("[Shade Hit Shadow] Complete, all tests pass!");

        return 1;
}
        
int main()
{
        TST_WorldCreate();
        TST_TestWorld();
        TST_WorldRayIntersect();
        TST_WorldShade();
        TST_WorldColorAt();
        TST_PointInShadow();
        TST_ShadeHitInShadow();

        mem_free_all();
        return 0;
}
