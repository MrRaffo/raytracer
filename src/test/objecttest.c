#include <stdio.h>
#include <assert.h>

#include <geometry/g_object.h>
#include <geometry/matrix.h>
#include <scene/material.h>
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

int TST_SetMaterial()
{
        struct g_object *s = test_sphere();
        struct material m = material_new(color_new(0.9, 0.1, 0.0), 0.1, 0.8, 0.9, 100.0);

        object_set_material(s, m);

        assert(material_equal(s->material, m) == 1);

        log_msg("[Object Set Material] Complete, all tests pass!");

        return 1;
}

int main()
{
        TST_SetTransform();
        TST_SetMaterial();

        mem_free_all();

        return 0;
}
