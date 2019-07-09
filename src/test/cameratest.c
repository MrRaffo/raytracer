#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <scene/camera.h>
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

int main()
{
        TST_CameraNew();

        mem_free_all();

        return 0;
}
