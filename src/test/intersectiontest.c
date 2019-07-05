#include <stdio.h>
#include <assert.h>

#include <geometry/g_object.h>
#include <geometry/intersection.h>
#include <geometry/tuple.h>
#include <geometry/ray.h>

#include <util/mem.h>
#include <util/log.h>

int TST_IntersectionLength()
{
        struct i_list *list = i_list_new();
        struct g_object *s = test_sphere();
        struct intersection *i1 = intersection_new(1.0, s);
        struct intersection *i2 = intersection_new(2.0, s);
        struct intersection *i3 = intersection_new(3.0, s);
        add_intersection(list, i1);
        add_intersection(list, i2);
        add_intersection(list, i3);

        assert(list->count == 3);

        fprintf(stdout, "[I_LIST LENGTH] Complete, all tests pass!\n");
        return 1;
}

int TST_IntersectionIndex()
{
        struct i_list *list = i_list_new();
        struct g_object *s = test_sphere();
        struct intersection *i2 = intersection_new(2.0, s);
        struct intersection *i1 = intersection_new(1.0, s);
        struct intersection *i3 = intersection_new(3.0, s);
        struct intersection *i4 = intersection_new(-3.0, s);
        struct intersection *i5 = intersection_new(-2.0, s);
        struct intersection *i6 = intersection_new(-1.0, s);
        add_intersection(list, i1);
        add_intersection(list, i2);
        add_intersection(list, i3);
        add_intersection(list, i4);
        add_intersection(list, i5);
        add_intersection(list, i6);

        // index 0 should be the first intersection in the positive ray dir
        // the 'start' node of the list should always be passed over
        struct intersection *i = get_intersection(list, 0);
        assert(double_equal(i->t, 1.0) == 1);
        i = get_intersection(list, 1);
        assert(double_equal(i->t, 2.0) == 1);
        i = get_intersection(list, 2);
        assert(double_equal(i->t, 3.0) == 1);

        // a negative index checks the ray backwards from the origin
        i = get_intersection(list, -1);
        assert(double_equal(i->t, -1.0) == 1);
        i = get_intersection(list, -2);
        assert(double_equal(i->t, -2.0) == 1);
        i = get_intersection(list, -3);
        assert(double_equal(i->t, -3.0) == 1);

        // invalid indices should return null
        assert(get_intersection(list, 99) == NULL);
        assert(get_intersection(list, -9) == NULL);

        fprintf(stdout, "[I_LIST INDEX] Complete, all tests pass!\n");
        return 1;
}

int TST_IntersectionHit()
{
        struct g_object *s = test_sphere();
        struct i_list *list = i_list_new();
        struct intersection *res;
        struct intersection *i1 = intersection_new(1.0, s);
        struct intersection *i2 = intersection_new(2.0, s);
        struct intersection *i3 = intersection_new(-3.0, s);
        struct intersection *i4 = intersection_new(2.0, s);

        add_intersection(list, i1);
        add_intersection(list, i2);

        res = i_list_hit(list);
        assert(res == i1);

        list = i_list_new();
        i1 = intersection_new(-1.0, s);
        i2 = intersection_new(1.0, s);
        add_intersection(list, i1);
        add_intersection(list, i2);

        res = i_list_hit(list);
        assert(res == i2);

        list = i_list_new();
        i1 = intersection_new(-2.0, s);
        i2 = intersection_new(-1.0, s);
        add_intersection(list, i1);
        add_intersection(list, i2);

        res = i_list_hit(list);
        assert(res == NULL);

        list = i_list_new();
        i1 = intersection_new(5.0, s);
        i2 = intersection_new(7.0, s);
        add_intersection(list, i1);
        add_intersection(list, i2);
        add_intersection(list, i3);
        add_intersection(list, i4);

        res = i_list_hit(list);
        assert(res == i4);

        fprintf(stdout, "[I_LIST HIT] Complete, all tests pass!\n");
        return 1;
}

TST_PreComputations()
{
        struct ray r = ray_new(tuple_point(0.0, 0.0, -5.0),
                               tuple_vector(0.0, 0.0, 1.0));
        struct g_object *s = test_sphere();
        struct intersection *i = intersection_new(4.0, s);

        struct i_comp comps = i_pre_compute(i, r);

        assert(double_equal(comps.t, 4.0) == 1);
        assert(tuple_equal(comps.point, tuple_point(0.0, 0.0, -1.0)) == 1);
        assert(tuple_equal(comps.eye_v, tuple_vector(0.0, 0.0, -1.0)) == 1 );
        assert(tuple_equal(comps.normal, tuple_vector(0.0, 0.0, -1.0)) == 1);

        log_msg("[Pre Computations] Complete, all tests pass!");

        return 1;
}


int main() {
        
        TST_IntersectionLength();
        TST_IntersectionIndex();
        TST_IntersectionHit();
        TST_PreComputations();

        mem_free_all();

        return 0;
}
