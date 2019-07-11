#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <scene/camera.h>
#include <geometry/ray.h>
#include <geometry/matrix.h>

#include <util/log.h>
#include <util/mem.h>

int TST_CameraNew()
{
        struct camera c = camera(160, 120, M_PI/2.0);

        assert(c.hsize == 160);
        assert(c.vsize == 120);
        assert(double_equal(c.field_of_view, M_PI/2.0) == 1);
        assert(matrix_equal(c.transform, matrix_identity(4)) == 1);

        log_msg("[Camera New] Complete, all tests pass!");

        return 1;
}

int TST_CameraPixelSize()
{
        // horizontal/landscape camera
        struct camera c = camera(200, 125, M_PI/2.0);
        assert(double_equal(c.pixel_size, 0.01) == 1);

        // verical/portrait camera
        c = camera(125, 200, M_PI/2.0);
        assert(double_equal(c.pixel_size, 0.01) == 1);

        log_msg("[Pixel Size] Complete, all tests pass!");
        return 1;
}

int TST_CameraRayForPixel()
{
        struct camera c = camera(201, 101, M_PI/2.0);
        struct ray r = camera_ray_for_pixel(c, 100, 50);

        assert(tuple_equal(r.org, tuple_point(0.0, 0.0, 0.0)) == 1);
        assert(tuple_equal(r.dir, tuple_vector(0.0, 0.0, -1.0)) == 1);

        r = camera_ray_for_pixel(c, 0, 0);
        assert(tuple_equal(r.org, tuple_point(0.0, 0.0, 0.0)) == 1);
        assert(tuple_equal(r.dir, tuple_vector(0.66519, 0.33259, -0.66851)) == 1);

        c.transform = matrix_multiply(matrix_rotate_y(M_PI/4.0), matrix_translate(0.0, -2.0, 5.0));
        r = camera_ray_for_pixel(c, 100, 50);

        assert(tuple_equal(r.org, tuple_point(0.0, 2.0, -5.0)) == 1);
        assert(tuple_equal(r.dir, tuple_vector(sqrt(2.0)/2.0, 0.0, -sqrt(2.0)/2.0)) == 1);

        log_msg("[Ray for Pixel] Complete, all tests pass!");
        return 1;
}

int TST_CameraRender()
{
        struct world *w = test_world();
        struct camera c = camera(11, 11, M_PI / 2.0);
        struct tuple from = tuple_point(0.0, 0.0, -5.0);
        struct tuple to = tuple_point(0.0, 0.0, 0.0);
        struct tuple up = tuple_vector(0.0, 1.0, 0.0);
        c.transform = matrix_view_transform(from, to, up);

        struct canvas image = camera_render(c, w);
        struct color result = color_new(0.38066, 0.47583, 0.2855);
        struct color test_color = canvas_read_pixel(image, 5, 5);

        assert(color_equal(result, test_color) == 1);

        log_msg("[Render] Complete, all tests pass!");
        return 1;
}

int main()
{
        TST_CameraNew();
        TST_CameraPixelSize();
        TST_CameraRayForPixel();
        TST_CameraRender();

        mem_free_all();

        return 0;
}
