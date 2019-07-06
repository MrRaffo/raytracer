#include <stdio.h>

#include <geometry/intersection.h>
#include <geometry/g_object.h>
#include <geometry/tuple.h>
#include <geometry/ray.h>

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
struct i_list *i_list_new()
{
        struct intersection *i = intersection_new(0.0, NULL);
        struct i_node *node = (struct i_node *)mem_alloc(sizeof(struct i_node));
        node->xs = i;
        node->next = NULL;
        node->prev = NULL;
        struct i_list *list = (struct i_list *)mem_alloc(sizeof(struct i_list));
        list->count = 0;
        list->bottom = node;
        list->start = node;
        return list;
}

/* print the intersection list, mostly for debugging */
void i_list_print(struct i_list *list)
{
        struct i_node *ptr = list->bottom;
        while(ptr->next != NULL) {
                // skip over 'start' node
                if (ptr->xs->obj == NULL) { 
                        ptr = ptr->next;
                        continue; 
                } 
                
                printf("Intersection at %g\n", ptr->xs->t);
                printf("ptrs: %p, %p, %p\n\n", ptr, ptr->prev, ptr->next);
                ptr = ptr->next;
        }

        printf("Intersection at %g\n", ptr->xs->t);
        printf("ptrs: %p, %p, %p\n\n", ptr, ptr->prev, ptr->next);

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
                new->next = ptr;
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

/* return intersection by index, negative numbers traverse the ray backwards
* ie, any negative index will be behind the origin of the ray */
struct intersection *get_intersection(struct i_list *list, int index)
{
        if (list->count == 0) { return NULL; }

        struct i_node *ptr = list->start;
        if (index > list->count || index < list->count *-1) {
                log_err("Invalid index: %d of %d\n", index, list->count);
                return NULL;
        }
        
        if (index < 0) {
                while (index < 0 && ptr->prev != NULL) {
                        ptr = ptr->prev;
                        index++;
                }
        } else {
                index++;        // starting on -1 essentially as first node doesn't count
                while (index > 0 && ptr->next != NULL) {
                        ptr = ptr->next;
                        index--;
                }
        }

        if (index != 0) {
                printf("Index = %d\n", index);
                log_err("Error finding index\n");
                return NULL;
        }

        return ptr->xs;
}

/* return the first intersection from the origin of a ray in the
 * direction of the ray */
struct intersection *i_list_hit(struct i_list *list)
{
        return get_intersection(list, 0);
}

/* precompute the state of an intersection */
struct i_comp i_pre_compute(struct intersection *i, struct ray r)
{
        double t = i->t;
        struct g_object *obj = i->obj;
        struct tuple point = ray_position(r, t);
        struct tuple eye_v = tuple_negate(r.dir);
        struct tuple normal = object_normal_at(obj, point);
        
        // check if ray is crossing bounday from inside or outside
        int inside;
        if (vector_dot(normal, eye_v) < 0.0) {
                inside  = 1;
                normal = tuple_negate(normal);
        } else {
                inside = 0;
        }

        struct i_comp comp = {t, obj, point, eye_v, normal, inside};
        return comp;
}

