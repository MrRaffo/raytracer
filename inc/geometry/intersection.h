#ifndef __intersection_h__
#define __intersection_h__

#include <geometry/gmaths.h>
#include <geometry/g_object.h>

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

/* create a new intersection */
struct intersection *intersection_new(double t, struct g_object *s);

/* create a new intersection list */
struct i_list i_list_new();

/* add a new intersection to the list, returns 1 on success, 0 on fail */
int add_intersection(struct i_list *list, struct intersection *i);

#endif // __intersection_h__
