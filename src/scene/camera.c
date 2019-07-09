#include <stdio.h>

#include <scene/camera.h>
#include <geometry/matrix.h>
#include <geometry/tuple.h>

#include <util/log.h>
#include <util/mem.h>

/* create a new camera, transform is identity matrix */
struct camera camera(int hsize, int vsize, double field_of_view)
{
        struct camera c = {hsize, vsize, field_of_view, matrix_identity(4)};
        return c;
}

