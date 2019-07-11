#ifndef __camera_h__
#define __camera_h__

#include <geometry/matrix.h>
#include <graphics/canvas.h>
#include <scene/world.h>

struct camera {
        int hsize;      // width in pixels
        int vsize;      // height in pixels
        double pixel_size;
        double half_width;
        double half_height;
        double field_of_view;
        struct matrix transform;
};

/* create a new camera, transform is identity matrix */
struct camera camera(int hsize, int vsize, double field_of_view);

/* find the ray that originates at the camera and hits the canvas at the given
 * coordinate, the canvas is 1 world unit from the camera */
struct ray camera_ray_for_pixel(struct camera c, int x, int y);

/* render the world to the canvas */
struct canvas camera_render(struct camera c, struct world *w);

#endif // __camera_h__
