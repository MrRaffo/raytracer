#include <stdio.h>

#include <graphics/canvas.h>
#include <graphics/color.h>
#include <util/mem.h>
#include <assert.h>

void TST_CanvasNew()
{
        struct canvas c = canvas_new(3, 3);
        
        canvas_print(c);
}

void TST_CanvasWrite()
{
        struct canvas c = canvas_new(3, 3);
        struct color col1 = color_new(1.0f, 0.5f, 0.4f);
        struct color col2 = color_new(0.2f, 0.2f, 0.02f);

        assert(canvas_write_pixel(c, 0, 0, col1) == 1);
        assert(canvas_write_pixel(c, 1, 0, col1) == 1);
        assert(canvas_write_pixel(c, 1, 1, col2) == 1);
        // this next one should fail and print an error
        fprintf(stdout, "Test error handling:\n");
        assert(canvas_write_pixel(c, 3, 2, col1) == 0);

        canvas_print(c);

        fprintf(stdout, "[Canvas Write] All tests complete - pass!\n");
}

void TST_CanvasRead()
{
        struct canvas can = canvas_new(3, 3);
        struct color col1 = color_new(1.0f, 0.5f, 0.0f);
        struct color col2 = color_new(1.0f, 0.5f, 0.0f);

        assert(!color_equal(canvas_read_pixel(can, 1, 1), col2));
        canvas_write_pixel(can, 1, 1, col1);
        assert(color_equal(canvas_read_pixel(can, 1, 1), col2));
        // this should produce error:
        fprintf(stdout, "Test error handling:\n");
        canvas_read_pixel(can, 4, 5);

        fprintf(stdout, "[Canvas Read] All tests complete - pass!\n");
}

void TST_CanvasExportToPPM()
{
        struct canvas c = canvas_new(200, 100);
        struct color col = color_new(0.7843f, 0.0627f, 0.1804f);

        for (int x = 0; x < c.w; x++) {
                for (int y = 0; y < c.h; y++) {
                        canvas_write_pixel(c, x, y, col);
                }
        }

        canvas_export_ppm(c, "img/exporttest.ppm");

        fprintf(stdout, "img/exporttest.ppm created\n");
        
        return;
}

int main()
{
        TST_CanvasNew();
        TST_CanvasWrite();
        TST_CanvasRead();
        TST_CanvasExportToPPM();

        mem_free_all();

        return 0;
}
        
