#ifndef __camera_h__
#define __camera_h__

#include <geometry/matrix.h>

struct camera {
        int hsize;      // width in pixels
        int vsize;      // height in pixels
        double field_of_view;
        struct matrix transform;
};

/* create a new camera, transform is identity matrix */
struct camera camera(int hsize, int vsize, double field_of_view);

#endif // __camera_h__
