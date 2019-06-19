#include <stdio.h>

#include <geometry/intersection.h>
#include <geometry/g_object.h>

#include <util/log.h>
#include <util/mem.h>

/* create a new intersection */
struct intersection *intersection_new(double t, struct g_object *s)
{
        struct intersection *i = (struct intersection *)mem_alloc(sizeof(struct intersection));
        i->t = t;
        i->obj = s;
        return i;
}

/* create a new intersection list */
struct i_list i_list_new()
{
        struct intersection *i = intersection_new(0.0, NULL);
        struct i_node *node = (struct i_node *)mem_alloc(sizeof(struct i_node));
        node->xs = i;
        node->next = NULL;
        node->prev = NULL;
        struct i_list list = {0, node, node};
        return list;
}

/* add a new intersection to the list, returns new length of list */
int add_intersection(struct i_list *list, struct intersection *i)
{
        struct i_node *ptr = list->bottom;

        if (i->t < ptr->xs->t) {
                // intersection is further back than any found yet
                ptr->prev = (struct i_node *)mem_alloc(sizeof(struct i_node));
                ptr->prev->xs = i;
                ptr->prev->next = ptr;
                ptr->prev->prev = NULL;
                list->bottom = ptr->prev;
                list->count += 1;
                return list->count;
        }

        while (ptr->next != NULL && ptr->xs->t < i->t) {
                ptr = ptr->next;
        }

        if (ptr->xs->t > i->t) {
                struct i_node *new = (struct i_node *)mem_alloc(sizeof(struct i_node));
                new->prev = ptr->prev;
                new->prev->next = new;
                ptr->prev = new;
                new->xs = i;
                list->count += 1;
                return list->count;
        }

        if (ptr->next == NULL) {
                ptr->next = (struct i_node *)mem_alloc(sizeof(struct i_node));
                ptr->next->prev = ptr;
                ptr->next->xs = i;
                ptr->next->next = NULL;
                list->count += 1;
                return list->count;
        }                

        log_wrn("Add Intersection to i_list failed");
        return list->count;
}



