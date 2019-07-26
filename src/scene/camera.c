#include <stdio.h>
#include <math.h>

#include <geometry/g_maths.h>
#include <graphics/canvas.h>
#include <scene/camera.h>
#include <scene/world.h>
#include <geometry/ray.h>
#include <geometry/matrix.h>
#include <geometry/tuple.h>

#include <util/log.h>
#include <util/mem.h>

/* create a new camera, transform is identity matrix */
struct camera camera(int hsize, int vsize, double field_of_view)
{
        
        // calculate size of pixels in world units
        double half_view = tan(field_of_view / 2.0);
        double aspect = (double)hsize / (double)vsize;
        double half_width, half_height;

        // landscape
        if (aspect >= 1.0) {
                half_width = half_view;
                half_height = half_view / aspect;
        } else {
        // portrait
                half_width = half_view * aspect;
                half_height = half_view;
        }

        double pixel_size = (half_width * 2.0) / (double)hsize;

        struct camera c = {hsize, vsize, pixel_size, half_width, half_height, 
                           field_of_view, matrix_identity(4)};
        
        return c;
}

/* find the ray that originates at the camera and hits the canvas at the given
 * coordinate, the canvas is 1 world unit from the camera */
struct ray camera_ray_for_pixel(struct camera c, int x, int y)
{
        // offset from edge of canvas to pixel centre
        double xoffset = ((double)x + 0.5) * c.pixel_size;
        double yoffset = ((double)y + 0.5) * c.pixel_size;

        // untransformed coordinates of the pixel in world space
        // (camera looks towards -z so +x is left)
        double world_x = c.half_width - xoffset;
        double world_y = c.half_height - yoffset;

        // transform the canvas point and the origin, then compute the ray
        // direction vector (canvas is at z = -1.0)
        struct tuple pixel = matrix_transform(matrix_inverse(c.transform), 
                                        tuple_point(world_x, world_y, -1.0));

        struct tuple origin = matrix_transform(matrix_inverse(c.transform),
                                        tuple_point(0.0, 0.0, 0.0));

        struct tuple direction = vector_normal(tuple_subtract(pixel, origin));

        struct ray r = ray_new(origin, direction);
        return r;
}

/* render the world to the canvas */
struct canvas camera_render(struct camera c, struct world *w)
{
        struct canvas image = canvas_new(c.hsize, c.vsize);

        int x, y;
        for (y = 0; y < c.vsize; y++) {
                for (x = 0; x < c.hsize; x++) {
                        struct ray r = camera_ray_for_pixel(c, x, y);
                        struct color col = world_color_at(w, r);
                        canvas_write_pixel(image, x, y, col);
                }
        }

        return image;
}

