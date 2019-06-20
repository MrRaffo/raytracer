#include <stdio.h>
#include <geometry/ray.h>
#include <geometry/sphere.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>
#include <geometry/g_object.h>
#include <geometry/intersection.h>

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
        struct g_object obj = {SHAPE_SPHERE};
        struct i_list *list = i_list_new();      // tracks intersections

        assert(ray_intersect(r, &obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->next->xs->t == 4.0f);
        assert(list->start->next->next->xs->t == 6.0f);

        list = i_list_new();
        o = tuple_point(0.0, 1.0, -5.0);
        r.org = o;

        assert(ray_intersect(r, &obj, list) == 1);
        assert(list->count == 1);
        assert(double_equal(list->start->next->xs->t, 5.0));

        list = i_list_new();
        o = tuple_point(0.0, 2.0, -5.0);
        r.org = o;

        assert(ray_intersect(r, &obj, list) == 0);
        assert(list->count == 0);

        list = i_list_new();
        o = tuple_point(0.0, 0.0, 0.0);
        r.org = o;

        assert(ray_intersect(r, &obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->prev->xs->t == -1.0);
        assert(list->start->next->xs->t == 1.0);

        list = i_list_new();
        o = tuple_point(0.0, 0.0, 5.0);
        r.org = o;

        assert(ray_intersect(r, &obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->prev->prev->xs->t == -6.0);
        assert(list->start->prev->xs->t == -4.0);

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
