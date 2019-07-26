
#include <stdio.h>
#include <math.h>

#include <scene/light.h>
#include <scene/material.h>
#include <geometry/tuple.h>
#include <graphics/color.h>
#include <geometry/g_maths.h>

#include <util/mem.h>
#include <util/log.h>

/* create a point light with given position and color */
const struct p_light p_light_new(struct tuple position, struct color intensity)
{
        struct p_light l = {position, intensity};
        return l;
}

/* returns 1 if 2 given lights are equal, 0 otherwise */
const int p_light_equal(struct p_light l1, struct p_light l2)
{
        return (tuple_equal(l1.position, l2.position) && 
                        color_equal(l1.intensity, l2.intensity));
}

/* the phong lighting model */
const struct color light_phong(struct material m, struct p_light l, 
        struct tuple p,  struct tuple eye_v, struct tuple obj_n, int in_shadow)
{
        struct color effective_color = color_multiply(m.color, l.intensity);
        struct tuple light_v = vector_normal(tuple_subtract(l.position, p));
        struct color ambient = color_scale(effective_color, m.ambient);
        struct color diffuse, specular;

        // dot product represents the cosine of the angle between the light
        // vector and the normal vector, a negative value indicates the light
        // is on the other side of the object
        double light_dot_normal = vector_dot(light_v, obj_n);
        if (light_dot_normal < 0.0) {
                diffuse = color_new(0.0, 0.0, 0.0);
                specular = color_new(0.0, 0.0, 0.0);
        } else {
                
                if (in_shadow == 1) {
                        return ambient;
                }

                diffuse = color_scale(effective_color, m.diffuse * light_dot_normal);

                // cosine between reflection vector and eye vector, a negative
                // value indicates the light is reflected away from the eye
                struct tuple reflect_v = vector_reflect(tuple_scale(light_v, -1.0), obj_n);
                double reflect_dot_eye = vector_dot(reflect_v, eye_v);

                if (reflect_dot_eye <= 0.0) {
                        specular = color_new(0.0, 0.0, 0.0);
                } else {
                        // calculate specular component
                        double factor = pow(reflect_dot_eye, m.shininess);
                        specular = color_scale(l.intensity, m.specular * factor);
                }
        }

        return color_add(ambient, color_add(diffuse, specular));
}
                        
