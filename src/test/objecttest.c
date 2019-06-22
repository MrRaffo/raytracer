#include <stdio.h>
#include <assert.h>

#include <geometry/g_object.h>
#include <geometry/matrix.h>
#include <util/mem.h>
#include <util/log.h>

int TST_SetTransform()
{
        struct g_object *s = test_sphere();
        struct matrix m = matrix_identity(4);
        assert(matrix_equal(m, s->transform) == 1);

        m = matrix_translate(2.0, 3.0, 4.0);
        object_transform(s, m);
        assert(matrix_equal(m, s->transform) == 1);

        fprintf(stdout, "[Object Set Transform] Complete, all tests pass!\n");

        return 1;
}

int main()
{
        TST_SetTransform();

        mem_free_all();

        return 0;
}
