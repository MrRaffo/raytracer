#include <stdio.h>
#include <geometry/matrix.h>
#include <geometry/gmaths.h>
#include <util/log.h>

#include <assert.h>

int TST_MatrixNew()
{
        return 0;
}

int TST_MatrixEqual()
{
        struct matrix m = matrix_new(4, 3);
        struct matrix n = matrix_new(4, 3);
        struct matrix p = matrix_new(3, 4);

        assert(matrix_equal(m, n) == 1);
        assert(matrix_equal(n, m) == 1);
        assert(matrix_equal(m, p) == 0);
        matrix_set(m, 1, 1, 3.5f);
        assert(matrix_equal(m, n) == 0);
        matrix_set(n, 1, 1, 3.4999999f);
        assert(matrix_equal(m, n) == 1);

        fprintf(stdout, "[Matrix Equal] All tests complete - pass!\n");

        return 1;
}

int TST_MatrixToString()
{
        struct matrix m = matrix_new(3, 4);
        fprintf(stdout, matrix_to_string(m));
        return 0;
}

int TST_MatrixSetGet()
{
        struct matrix m = matrix_new(2, 2);
        matrix_set(m, 1, 1, 1000.50011f);
        assert(matrix_get(m, 3, 5) == 0.0f);
        assert(matrix_get(m, 0, 0) == 0.0f);
        assert(float_equal(matrix_get(m, 1, 1), 1000.50011f) == 1);
        assert(matrix_set(m, 5, 5, 0.5f) == 0);
        fprintf(stdout, "%s\n", matrix_to_string(m));

        fprintf(stdout, "[Matrix Set and Get] Complete, all tests pass!\n");

        return 1;
}

int main()
{
        TST_MatrixNew();
        TST_MatrixEqual();
        TST_MatrixToString();
        TST_MatrixSetGet();

        mem_free_all();

        return 0;
}
