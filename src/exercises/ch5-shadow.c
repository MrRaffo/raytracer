#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/ray.h>
#include <geometry/matrix.h>
#include <geometry/g_object.h>

#include <graphics/color.h>
#include <graphics/canvas.h>

#include <util/mem.h>
#include <util/log.h>
#include <util/file.h>

#define WIDTH 200
#define HEIGHT 200

#define WALL_SIZE 7.0

#define CAM_POS_Z -5.0
#define WALL_POS_Z 10.0

int main()
{
        struct canvas canvas = canvas_new(WIDTH, HEIGHT);
        struct color red = color_new(0.7843, 0.0627, 0.1804);

        struct g_object *sphere = test_sphere();
        struct tuple cam_pos = tuple_point(0.0, 0.0, CAM_POS_Z);

        // size of pixels in world space
        double pixel_size = WALL_SIZE / WIDTH;
        double half = WALL_SIZE / 2.0;

        // cast the rays
        int x, y;
        for (y = 0; y < HEIGHT; y++) {
                double world_y = half - pixel_size * y;

                for(x = 0; x < WIDTH; x++) {
                        double world_x = half - pixel_size * x;

                        struct tuple pos = tuple_point(world_x, world_y, WALL_POS_Z);
                        struct ray ray = ray_new(cam_pos, 
                                vector_normal(tuple_subtract(pos, cam_pos)));

                        struct i_list *hits = i_list_new();
                        ray_intersect(ray, sphere, hits);

                        // if there is a hit, colour the pixel
                        if (i_list_hit(hits)) {
                                canvas_write_pixel(canvas, x, y, red);
                        }
                }
        }

        export_to_bmp(canvas, "img/shadow.bmp");

        mem_print();
        mem_free_all();

        return 0;
}
