#include <stdio.h>
#include <geometry/matrix.h>
#include <geometry/tuple.h>
#include <geometry/gmaths.h>
#include <util/log.h>
#include <util/mem.h>

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
        fprintf(stdout, "Print test:\n%s\n", matrix_to_string(m));
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

int TST_MatrixMultiply()
{
        struct matrix m = matrix_new(2, 3);
        struct matrix n = matrix_new(3, 2);
        float val = 1.0f;
        for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                        matrix_set(m, i, j, val);
                        val += 1.0f;
                }
        }

        val = 1.0f;
        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 2; j++) {
                        matrix_set(n, i, j, val);
                        val += 1.0f;
                }
        }

        struct matrix c = matrix_new(2, 2);
        matrix_set(c, 0, 0, 22.0f);
        matrix_set(c, 0, 1, 28.0f);
        matrix_set(c, 1, 0, 49.0f);
        matrix_set(c, 1, 1, 64.0f);

        assert(matrix_equal(matrix_multiply(m, n), c) == 1);
        assert(matrix_equal(matrix_multiply(m, c), n) == 0);

        fprintf(stdout, "[Matrix Multiply] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixTupleMultiply()
{
        struct matrix m = matrix_new(4, 4);
        float data[] = {1.0f, 2.0f, 3.0f, 4.0f, 2.0f, 4.0f, 4.0f, 2.0f,
                        8.0f, 6.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        m.matrix = data;

        struct tuple t = tuple_new(1.0f, 2.0f, 3.0f, 1.0f);
        
        struct tuple expect = tuple_new(18.0f, 24.0f, 33.0f, 1.0f);
        struct tuple result = matrix_tuple_multiply(m, t);
        assert(tuple_equal(result, expect) == 1);

        fprintf(stdout, "[Matrix * Tuple] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixIdentity()
{
        struct matrix m = matrix_identity(4);
        struct matrix i = matrix_new(4, 4);

        float id[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        i.matrix = id;

        struct matrix a = matrix_new(4, 4);

        float data[] = {0.0f, 1.0f, 2.0f, 4.0f, 1.0f, 2.0f, 4.0f, 8.0f,
                        2.0f, 4.0f, 8.0f, 16.0f, 4.0f, 8.0f, 16.0f, 32.0f};
        a.matrix = data;

        assert(matrix_equal(m, i) == 1);
        assert(matrix_equal(a, matrix_multiply(a, m)) == 1);

        fprintf(stdout, "[Matrix Identity] Complete, all tests pass!\n");

        return 1;
}

int TST_MatrixTranspose()
{
        struct matrix m = matrix_new(4, 4);
        struct matrix n = matrix_new(4, 4);

        float data[] = {0.0f, 9.0f, 3.0f, 0.0f,
                        9.0f, 8.0f, 0.0f, 8.0f,
                        1.0f, 8.0f, 5.0f, 3.0f,
                        0.0f, 0.0f, 5.0f, 8.0f};

        float datb[] = {0.0f, 9.0f, 1.0f, 0.0f,
                        9.0f, 8.0f, 8.0f, 0.0f,
                        3.0f, 0.0f, 5.0f, 5.0f,
                        0.0f, 8.0f, 3.0f, 8.0f};

        m.matrix = data;
        n.matrix = datb;

        assert(matrix_equal(matrix_transpose(m), n) == 1);
        assert(matrix_equal(matrix_transpose(matrix_identity(4)), matrix_identity(4)) == 1);
        assert(matrix_equal(matrix_transpose(matrix_identity(3)), matrix_identity(3)) == 1);
        assert(matrix_equal(matrix_transpose(matrix_identity(2)), matrix_identity(2)) == 1);

        fprintf(stdout, "[Matrix Transpose] Complete, all tests pass!\n");

        return 1;
}

int TST_MatrixDeterminant()
{
        // fail test
        assert(matrix_determinant(matrix_new(3, 3)) == 0.0f);
        struct matrix m = matrix_new(2, 2);
        assert(matrix_determinant(m) == 0.0f); // no error

        float data[] = {1.0f, 5.0f, -3.0f, 2.0f};
        m.matrix = data;
        assert(float_equal(matrix_determinant(m), 17.0f) == 1);

        fprintf(stdout, "[Matrix Determinant] Complete, all tests pass!\n");
        return 1;
}

int TST_Submatrix()
{
        struct matrix m3 = matrix_new(3, 3);
        float m3data[] = {1.0f, 5.0f, 0.0f,
                        -3.0f, 2.0f, 7.0f,
                        0.0f, 6.0f, -3.0f};
        struct matrix sm3 = matrix_new(2, 2);
        float sm3data[] = {-3.0f, 2.0f,
                         0.0f, 6.0f};

        struct matrix m4 = matrix_new(4, 4);
        float m4data[] = {-6.0f, 1.0f, 1.0f, 6.0f,
                          -8.0f, 5.0f, 8.0f, 6.0f,
                          -1.0f, 0.0f, 8.0f, 2.0f,
                          -7.0f, 1.0f, -1.0f, 1.0f};
        struct matrix sm4 = matrix_new(3, 3);
        float sm4data[] = {-6.0f, 1.0f, 6.0f,
                         -8.0f, 8.0f, 6.0f,
                         -7.0f, -1.0f, 1.0f};

        m3.matrix = m3data;
        sm3.matrix = sm3data;
        m4.matrix = m4data;
        sm4.matrix = sm4data;

        assert(matrix_equal(submatrix(m3, 0, 2), sm3) == 1);
        assert(matrix_equal(submatrix(m4, 2, 1), sm4) == 1);

        fprintf(stdout, "[Submatrix] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixMinor()
{
        struct matrix m = matrix_new(3, 3);
        float mdata[] = {1.0f, 5.0f, 0.0f,
                          -3.0f, 2.0f, 7.0f,
                          0.0f, 6.0f, -3.0f};
        m.matrix = mdata;

        struct matrix n = matrix_new(3, 3);
        float ndata[] = {-6.0f, 1.0f, 6.0f,
                         -8.0f, 8.0f, 6.0f,
                         -7.0f, -1.0f, 1.0f};
        n.matrix = ndata;

        assert(float_equal(matrix_minor(m, 1, 2), 6.0f) == 1);
        assert(float_equal(matrix_minor(m, 0, 0), -48.0f) == 1);
        assert(float_equal(matrix_minor(n, 2, 1), 12.0f) == 1);
        assert(float_equal(matrix_minor(n, 2, 2), -40.0f) == 1);

        fprintf(stdout, "[Matrix Minor] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixCofactor()
{
        struct matrix m = matrix_new(3, 3);
        float mdata[] = {3.0f, 5.0f, 0.0f,
                         2.0f, -1.0f, -7.0f,
                         6.0f, -1.0f, 5.0f};
        m.matrix = mdata;

        assert(float_equal(matrix_minor(m, 0, 0), -12.0f) == 1);
        assert(float_equal(matrix_cofactor(m, 0, 0), -12.0f) == 1);
        assert(float_equal(matrix_cofactor(m, 1, 0), -25.0f) == 1);

        fprintf(stdout, "[Matrix Cofactor] Complete, all tests pass\n");
        return 1;
}

int main()
{
        TST_MatrixNew();
        TST_MatrixEqual();
        TST_MatrixToString();
        TST_MatrixSetGet();
        TST_MatrixMultiply();
        TST_MatrixTupleMultiply();
        TST_MatrixIdentity();
        TST_MatrixTranspose();
        TST_MatrixDeterminant();
        TST_Submatrix();
        TST_MatrixMinor();
        TST_MatrixCofactor();

        mem_free_all();

        return 0;
}
