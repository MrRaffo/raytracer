#ifndef __intersection_h__
#define __intersection_h__

#include <geometry/gmaths.h>
#include <geometry/g_object.h>
#include <geometry/tuple.h>
#include <geometry/ray.h>

/* handles all ray collisions */

/* records the distance along a ray an intersection is found along with the
 * object being intersected */
struct intersection {
        double t;
        struct g_object *obj;
};

/* this struct records intersections found against an object when a ray is 
 * cast */
struct intersect {
        int found;
        struct intersection *xs[2];
};

/* a double linked list to record ray intersections with objects */
struct i_node {
        struct intersection *xs;
        struct i_node *next;
        struct i_node *prev;
};

struct i_list {
        int count;
        struct i_node *start;
        struct i_node *bottom;
};

struct i_comp {
        double t;
        struct g_object *obj;
        struct tuple point;
        struct tuple eye_v;
        struct tuple normal;
};

/* create a new intersection */
struct intersection *intersection_new(double t, struct g_object *s);

/* create a new intersection list */
struct i_list *i_list_new();

/* print the intersection list, mostly for debugging */
void i_list_print(struct i_list *i);

/* add a new intersection to the list, returns 1 on success, 0 on fail */
int add_intersection(struct i_list *list, struct intersection *i);

/* return intersection by index, negative numbers traverse the ray backwards
 * ie, any negative index will be behind the origin of the ray */
struct intersection *get_intersection(struct i_list *list, int index);

/* return the first intersection from the origin of a ray in the
 * direction of the ray */
struct intersection *i_list_hit(struct i_list *list);

/* precompute the state of an intersection */
struct i_comp i_pre_compute(struct intersection *i, struct ray r);

#endif // __intersection_h__
