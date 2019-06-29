#include <stdio.h>
#include <assert.h>

#include <scene/material.h>
#include <graphics/color.h>

#include <util/mem.h>
#include <util/log.h>

TST_TestMaterial()
{
        struct material m = test_material();
        assert(color_equal(m.color, color_new(1.0, 1.0, 1.0)) == 1);
        assert(double_equal(m.ambient, 0.1) == 1);
        assert(double_equal(m.diffuse, 0.9) == 1);
        assert(double_equal(m.specular, 0.9) == 1);
        assert(double_equal(m.shininess, 200.0) == 1);

        struct material m2 = test_material();
        assert(material_equal(m, m2) == 1);

        struct material m3 = material_new(color_new(1.0, 1.0, 1.0), 0.1, 0.9, 0.9, 200.0);
        assert(material_equal(m2, m3) == 1);

        log_msg("[Test Material] Complete, all tests pass!");

        return 1;
}

int main()
{
        TST_TestMaterial();

        mem_free_all(); // just in case...

        return 0;
}
