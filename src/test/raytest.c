#include <stdio.h>
#include <geometry/ray.h>
#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <geometry/g_maths.h>
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

        fprintf(stdout, "[Ray New] Complete, all tests pass!\n");
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

        fprintf(stdout, "[Ray Position] Complete, all tests pass!\n");
        return 1;
}

int TST_RaySphereIntersect()
{
        struct tuple o = tuple_point(0.0f, 0.0f, -5.0f);
        struct tuple d = tuple_vector(0.0f, 0.0f, 1.0f);
        struct ray r = ray_new(o, d);
        struct g_object *obj = test_sphere();
        struct i_list *list = i_list_new();      // tracks intersections

        assert(ray_intersect(r, obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->next->xs->t == 4.0f);
        assert(list->start->next->next->xs->t == 6.0f);

        list = i_list_new();
        o = tuple_point(0.0, 1.0, -5.0);
        r.org = o;

        assert(ray_intersect(r, obj, list) == 1);
        assert(list->count == 1);
        assert(double_equal(list->start->next->xs->t, 5.0));

        list = i_list_new();
        o = tuple_point(0.0, 2.0, -5.0);
        r.org = o;

        assert(ray_intersect(r, obj, list) == 0);
        assert(list->count == 0);

        list = i_list_new();
        o = tuple_point(0.0, 0.0, 0.0);
        r.org = o;

        assert(ray_intersect(r, obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->prev->xs->t == -1.0);
        assert(list->start->next->xs->t == 1.0);

        list = i_list_new();
        o = tuple_point(0.0, 0.0, 5.0);
        r.org = o;

        assert(ray_intersect(r, obj, list) == 2);
        assert(list->count == 2);
        assert(list->start->prev->prev->xs->t == -6.0);
        assert(list->start->prev->xs->t == -4.0);

        fprintf(stdout, "[Ray Sphere Intersect] Complete, all tests pass!\n");

        return 1;
}

int TST_RayTransform()
{
        struct tuple o = tuple_point(1.0, 2.0, 3.0);
        struct tuple d = tuple_vector(0.0, 1.0, 0.0);
        struct ray r = ray_new(o, d);

        struct matrix m = matrix_translate(3.0, 4.0, 5.0);
        struct matrix t = transform(&m, NULL);

        struct ray r2 = ray_transform(r, t);

        struct tuple expected_org = tuple_point(4.0, 6.0, 8.0);
        struct tuple expected_dir = tuple_vector(0.0, 1.0, 0.0);

        assert(tuple_equal(r2.org, expected_org) == 1);
        assert(tuple_equal(r2.dir, expected_dir) == 1);

        m = matrix_scale(2.0, 3.0, 4.0);
        t = transform(&m, NULL);

        r2 = ray_transform(r, t);

        assert(tuple_equal(r2.org, tuple_point(2.0, 6.0, 12.0)) == 1);
        assert(tuple_equal(r2.dir, tuple_vector(0.0, 3.0, 0.0)) == 1);

        fprintf(stdout, "[Ray Transform] Complete, all tests pass!\n");
        return 1;
}

// check a ray will intersect a transformed sphere
int TST_RaySphereTransformIntersect()
{
        // test for a scaled sphere
        struct g_object *s = test_sphere();
        struct matrix m = matrix_scale(2.0, 2.0, 2.0);
        object_transform(s, m);

        struct tuple org = tuple_point(0.0, 0.0, -5.0);
        struct tuple dir = tuple_vector(0.0, 0.0, 1.0);
        struct ray r = ray_new(org, dir);

        struct i_list *list = i_list_new();

        ray_intersect(r, s, list);

        assert(list->count == 2);
        assert(double_equal(get_intersection(list, 0)->t, 3.0) == 1);
        assert(double_equal(get_intersection(list, 1)->t, 7.0) == 1);

        // test for a translated sphere
        struct matrix n = matrix_translate(5.0, 0.0, 0.0);
        object_transform(s, n);

        struct i_list *list2 = i_list_new();
        ray_intersect(r, s, list2);

        printf("XS: %d\n", list2->count);
        assert(list2->count == 0);
        
        fprintf(stdout, "[Ray Sphere Transformed Intersect] Complete, all tests pass!\n");
        return 1;
}

int main()
{
        TST_RayNew();
        TST_RayPosition();
        TST_RaySphereIntersect();
        TST_RayTransform();
        TST_RaySphereTransformIntersect();

        mem_free_all();

        return 0;
}
