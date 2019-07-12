
#include <stdio.h>

#include <geometry/gmaths.h>
#include <scene/material.h>
#include <graphics/color.h>

/* create a default material with default parameters */
const struct material test_material()
{
        struct color col = color_new(1.0, 1.0, 1.0);
        struct material m = {col, 0.1, 0.9, 0.9, 200.0};
        return m;
}

/* create a default white material */
const struct material material()
{
        return test_material();
}

/* create a new material with given properties */
const struct material material_new(struct color color, double ambient, 
                        double diffuse, double specular, double shininess)
{
        struct material m = {color, ambient, diffuse, specular, shininess};
        return m;
}

/* return 1 if 2 passed materials are the same, 0 otherwise */
const int material_equal(struct material m1, struct material m2)
{
        return (color_equal(m1.color, m2.color) &&
                double_equal(m1.ambient, m2.ambient) &&
                double_equal(m1.diffuse, m2.diffuse) &&
                double_equal(m1.specular, m2.specular) &&
                double_equal(m1.shininess, m2.shininess));
}


