#include <stdio.h>

#include <scene/world.h>
#include <scene/light.h>
#include <geometry/tuple.h>
#include <graphics/color.h>
#include <geometry/g_object.h>
#include <geometry/sphere.h>
#include <geometry/ray.h>
#include <geometry/intersection.h>

#include <util/mem.h>
#include <util/log.h>

/* create a new world with no objects or lights */
struct world *world_new()
{
        struct world *w = (struct world *)mem_alloc(sizeof(struct world));
        w->objects = NULL;
        w->lights = NULL;
        return w;
}

/* create a world containing two spheres and a light for testing */
struct world *test_world()
{
        struct g_object *s1 = test_sphere();
        struct g_object *s2 = test_sphere();
        struct material m1 = material_new(color_new(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
        struct matrix mat = matrix_scale(0.5, 0.5, 0.5);

        object_set_material(s1, m1);
        object_transform(s2, mat);

        struct p_light l = p_light_new(tuple_point(-10.0, 10.0, -10.0), 
                                     color_new(1.0, 1.0, 1.0));

        struct world *w = world_new();
        world_add_object(w, s1);
        world_add_object(w, s2);
        world_add_light(w, l);

        return w;
}

/* add an object to the world, return 1 on success */
int world_add_object(struct world *w, struct g_object *obj)
{
        struct w_obj_node *ptr, *new;
        if (w->objects == NULL) {
                w->objects = (struct w_obj_node *)mem_alloc(sizeof(struct w_obj_node));  
                new = w->objects;
                new->prev = NULL;
                new->next = NULL;
        } else {
                ptr = w->objects;
                // get to last object in list
                while(ptr->next != NULL) {
                        ptr = ptr->next;
                }
                new = (struct w_obj_node *)mem_alloc(sizeof(struct w_obj_node));
                ptr->next = new;
                new->prev = ptr;
                new->next = NULL;
        }

        new->object = obj;

        return 1;
}

/* add a light to the world, return 1 on success */
int world_add_light(struct world *w, struct p_light light)
{
        struct w_light_node *ptr, *new;
        if (w->lights == NULL) {
                w->lights = (struct w_light_node *)mem_alloc(sizeof(struct w_light_node));
                new = w->lights;
                new->prev = NULL;
                new->next = NULL;
        } else {
                ptr = w->lights;
                // get to last space in list
                while(ptr->next != NULL) {
                        ptr = ptr->next;
                }
                new = (struct w_light_node *)mem_alloc(sizeof(struct w_light_node));
                ptr->next = new;
                new->prev = ptr;
                new->next = NULL;
        }

        new->light = light;

        return 1;
}

/* return 1 if an object identical to the one passed is in the world */
int world_has_object(struct world *w, struct g_object *obj)
{
        struct w_obj_node *ptr = w->objects;

        if (ptr == NULL) { return 0; }
        do {
                if (object_equal(ptr->object, obj)) {
                        return 1;
                }
        } while ((ptr = ptr->next) != NULL);

        return 0;
}

/* return 1 if there is an identical light in the world */
int world_has_light(struct world *w, struct p_light light)
{
        struct w_light_node *ptr = w->lights;

        if (ptr == NULL) { return 0; }
        do {
                if (p_light_equal(ptr->light, light)) {
                        return 1;
                }
        } while ((ptr = ptr->next) != NULL);
        
        return 0;
}

/* count total intersections with given ray against all objects in world
 * returns number of intersections found */
int world_ray_intersections(struct world *w, struct ray ray, struct i_list *list)
{
        struct w_obj_node *ptr = w->objects;
        int count = 0;
        if (ptr == NULL) { return 0; }

        do {
               count += ray_intersect(ray, ptr->object, list);
        } while((ptr = ptr->next) != NULL);

        return count;
}

/* calculate the color of an intersection */
/* TODO - this currently only uses the first light in the world */
struct color world_shade_hit(struct world *w, struct i_comp comps)
{
        return light_phong(comps.obj->material,
                           w->lights->light,
                           comps.point, comps.eye_v, comps.normal);
}
