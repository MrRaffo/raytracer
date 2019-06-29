#ifndef __material_h__
#define __material_h__

#include <graphics/color.h>

struct material {
        struct color color;
        double ambient;
        double diffuse;
        double specular;
        double shininess;
};

/* create a default material with default parameters */
const struct material test_material();

/* create a new material with given properties */
const struct material material_new(struct color color, double ambient, 
                        double diffuse, double specular, double shininess);

/* return 1 if 2 passed materials are the same, 0 otherwise */
const int material_equal(struct material m1, struct material m2);


#endif // __material_h__

