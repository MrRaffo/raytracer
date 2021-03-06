#ifndef __world_h__
#define __world_h__

#include <scene/light.h>

/* forward declarations */
struct g_object;
struct ray;
struct i_list;
struct i_comp;

struct w_obj_node {
        struct g_object *object;
        struct w_obj_node *next;
        struct w_obj_node *prev;
};

struct w_light_node {
        struct p_light light;
        struct w_light_node *next;
        struct w_light_node *prev;
};

struct world {
        struct w_obj_node *objects;
        struct w_light_node *lights;
};


/* create a new world with no objects or lights */
struct world *world_new();

/* create a world containing two spheres and a light for testing */
struct world *test_world();

/* add an object to the world, return 1 on success */
int world_add_object(struct world *w, struct g_object *obj);

/* add a light to the world, return 1 on success */
int world_add_light(struct world *w, struct p_light l);

/* return 1 if an object identical to the one passed is in the world */
int world_has_object(struct world *w, struct g_object *obj);

/* return 1 if there is an identical light in the world */
int world_has_light(struct world *w, struct p_light light);

/* count total intersections with given ray against all objects in world
 * returns number of intersections found */
int world_ray_intersections(struct world *w, struct ray r, struct i_list *list);

/* calculate the color of an intersection */
struct color world_shade_hit(struct world *w, struct i_comp comps);

/* wrapper for intersect, pre_compute and shade_hit */
struct color world_color_at(struct world *w, struct ray r);

/* check if a point in the world is in shadow by casting a ray from the light
 * source to the point and checking for objects lying in the path, return 1 
 * if so */
int world_point_is_shadowed(struct world *w, struct p_light l, struct tuple point);

#endif // __world_h__
