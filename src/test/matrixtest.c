#include <stdio.h>
#include <math.h>

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

int TST_MatrixCopy()
{
        struct matrix m = matrix_new(3, 3);
        float data[] = {3.0f, 30.0f, 1.0f,
                        1.0f, 6.0f, 10.f,
                        0.0f, 0.5f, 4.0f};
        m.matrix = data;

        struct matrix copy = matrix_copy(m);

        assert(matrix_equal(m, copy) == 1);

        fprintf(stdout, "[Matrix Copy] Complete, all tests pass!\n");

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
        struct tuple result = matrix_transform(m, t);
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

int TST_Matrix2Determinant()
{
        // fail test
        assert(matrix_2determinant(matrix_new(3, 3)) == 0.0f);
        struct matrix m = matrix_new(2, 2);
        assert(matrix_2determinant(m) == 0.0f); // no error

        float data[] = {1.0f, 5.0f, -3.0f, 2.0f};
        m.matrix = data;
        assert(float_equal(matrix_2determinant(m), 17.0f) == 1);

        fprintf(stdout, "[Matrix 2 Determinant] Complete, all tests pass!\n");
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

int TST_MatrixDeterminant()
{
        struct matrix m3 = matrix_new(3, 3);
        float m3data[] = {1.0f, 2.0f, 6.0f,
                          -5.0f, 8.0f, -4.0f,
                          2.0f, 6.0f, 4.0f};
        m3.matrix = m3data;


        struct matrix m4 = matrix_new(4, 4);
        float m4data[] = {-2.0f, -8.0f, 3.0f, 5.0f,
                          -3.0f, 1.0f, 7.0f, 3.0f,
                          1.0f, 2.0f, -9.0f, 6.0f,
                          -6.0f, 7.0f, 7.0f, -9.0f};
        m4.matrix = m4data;

        assert(float_equal(matrix_cofactor(m3, 0, 0), 56.0f) == 1);
        assert(float_equal(matrix_cofactor(m3, 0, 1), 12.0f) == 1);
        assert(float_equal(matrix_cofactor(m3, 0, 2), -46.0f) == 1);
        assert(float_equal(matrix_determinant(m3), -196.0f) == 1);

        assert(float_equal(matrix_cofactor(m4, 0, 0), 690.0f) == 1);
        assert(float_equal(matrix_cofactor(m4, 0, 1), 447.0f) == 1);
        assert(float_equal(matrix_cofactor(m4, 0, 2), 210.0f) == 1);
        assert(float_equal(matrix_cofactor(m4, 0, 3), 51.0f) == 1);
        assert(float_equal(matrix_determinant(m4), -4071.0f) == 1);

        fprintf(stdout, "[Matrix Determinant] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixInvertible()
{
        struct matrix invertible = matrix_new(4, 4);
        float minv[] = {6.0f, 4.0f, 4.0f, 4.0f,
                        5.0f, 5.0f, 7.0f, 6.0f,
                        4.0f, -9.0f, 3.0f, -7.0f,
                        9.0f, 1.0f, 7.0f, -6.0f};
        invertible.matrix = minv;

        struct matrix noninvertible = matrix_new(4, 4);
        float mnon[] = {-4.0f, 2.0f, -2.0f, -3.0f,
                        9.0f, 6.0f, 2.0f, 6.0f,
                        0.0f, -5.0f, 1.0f, -5.0f,
                        0.0f, 0.0f, 0.0f, 0.0f};
        noninvertible.matrix = mnon;

        assert(matrix_invertible(invertible) == 1);
        assert(matrix_invertible(noninvertible) == 0);

        fprintf(stdout, "[Matrix Invertible] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixInverse()
{
        struct matrix m1 = matrix_new(4, 4);
        struct matrix m2 = matrix_new(4, 4);
        struct matrix m3 = matrix_new(4, 4);

        float m1data[] = {-5.0f, 2.0f, 6.0f, -8.0f,
                          1.0f, -5.0f, 1.0f, 8.0f,
                          7.0f, 7.0f, -6.0f, -7.0f,
                          1.0f, -3.0f, 7.0f, 4.0f};

        float m2data[] = {8.0f, -5.0f, 9.0f, 2.0f,
                          7.0f, 5.0f, 6.0f, 1.0f,
                          -6.0f, 0.0f, 9.0f, 6.0f,
                          -3.0f, 0.0f, -9.0f, -4.0f};

        float m3data[] = {9.0f, 3.0f, 0.0f, 9.0f,
                          -5.0f, -2.0f, -6.0f, -3.0f,
                          -4.0f, 9.0f, 6.0f, 4.0f,
                          -7.0f, 6.0f, 6.0f, 2.0f};

        struct matrix im1 = matrix_new(4, 4);
        struct matrix im2 = matrix_new(4, 4);
        struct matrix im3 = matrix_new(4, 4);

        float im1data[] = {0.21805f, 0.45113f, 0.24060f, -0.04511f,
                          -0.80827f, -1.45677f, -0.44361f, 0.52068f,
                          -0.07895f, -0.22368f, -0.05263f, 0.19737f,
                          -0.52256f, -0.81391f, -0.30075f, 0.30639f};

        float im2data[] = {-0.15385f, -0.15385f, -0.28205f, -0.53846f,
                           -0.07692f, 0.12308f, 0.02564f, 0.03077f,
                           0.35897f, 0.35897f, 0.43590f, 0.92308f,
                           -0.69231f, -0.69231f, -0.76923f, -1.92308f};

        float im3data[] = {-0.04074f, -0.07778f, 0.14444f, -0.22222f,
                           -0.07778f, 0.03333f, 0.36667f, -0.33333f,
                           -0.02901f, -0.14630f, -0.10926f, 0.12963f,
                           0.17778f, 0.06667f, -0.26667f, 0.33333f};

        m1.matrix = m1data;
        m2.matrix = m2data;
        m3.matrix = m3data;
        im1.matrix = im1data;
        im2.matrix = im2data;
        im3.matrix = im3data;

        assert(matrix_equal(matrix_inverse(m1), im1) == 1);
        assert(matrix_equal(matrix_inverse(m2), im2) == 1);
        assert(matrix_equal(matrix_inverse(m3), im3) == 1);

        fprintf(stdout, "[Matrix Inverse] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixTranslate()
{
        struct tuple point = tuple_point(-3.0f, 4.0f, 5.0f);
        struct matrix transform = matrix_translate(5.0f, -3.0f, 2.0f);
        struct tuple tpoint = tuple_new(2.0f, 1.0f, 7.0f, 1.0f);
        
        assert(tuple_equal(matrix_transform(transform, point), tpoint) == 1);
        tpoint = tuple_new(-8.0f, 7.0f, 3.0f, 1.0f);
        assert(tuple_equal(matrix_transform(matrix_inverse(transform), point), tpoint));
        
        struct tuple vec =  tuple_vector(1.0f, 2.0f, 3.0f);
        assert(tuple_equal(matrix_transform(transform, vec), vec));

        fprintf(stdout, "[Matrix Translate] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixScale()
{
        struct matrix transform = matrix_scale(2.0f, 3.0f, 4.0f);
        struct tuple point = tuple_point(-4.0f, 6.0f, 8.0f);
        struct tuple vec = tuple_vector(-4.0f, 6.0f, 8.0f);

        struct tuple scaled_point = tuple_point(-8.0f, 18.0f, 32.0f);
        struct tuple scaled_vec = tuple_vector(-8.0f, 18.0f, 32.0f);

        assert(tuple_equal(matrix_transform(transform, point), scaled_point) == 1);
        assert(tuple_equal(matrix_transform(transform, vec), scaled_vec) == 1);

        transform = matrix_inverse(transform);
        scaled_vec = tuple_vector(-2.0f, 2.0f, 2.0f);
        assert(tuple_equal(matrix_transform(transform, vec), scaled_vec) == 1);
<<<<<<< HEAD

        // reflection on x axis
        transform = matrix_scale(-1.0f, 1.0f, 1.0f);
        point = tuple_point(2.0f, 3.0f, 4.0f);
        scaled_point = tuple_point(-2.0f, 3.0f, 4.0f);
        assert(tuple_equal(matrix_transform(transform, point), scaled_point) == 1);

        fprintf(stdout, "[Matrix Scale] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateX()
{
        struct tuple point = tuple_point(0.0f, 1.0f, 0.0f);
        struct matrix rot45 = matrix_rotate_x(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_x(M_PI / 2.0f);

        struct tuple point45 = tuple_point(0.0f, (sqrt(2.0f)/2.0f),(sqrt(2.0f)/2.0f));
        struct tuple point90 = tuple_point(0.0f, 0.0f, 1.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate X] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateY()
{
        struct tuple point = tuple_point(0.0f, 0.0f, 1.0f);
        struct matrix rot45 = matrix_rotate_y(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_y(M_PI / 2.0f);

        struct tuple point45 = tuple_point((sqrt(2.0f)/2.0f), 0.0f, (sqrt(2.0f)/2.0f));
        struct tuple point90 = tuple_point(1.0f, 0.0f, 0.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate Y] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateZ()
{
        struct tuple point = tuple_point(0.0f, 1.0f, 0.0f);
        struct matrix rot45 = matrix_rotate_z(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_z(M_PI / 2.0f);

        struct tuple point45 = tuple_point(-1.0f * (sqrt(2.0f)/2.0f), (sqrt(2.0f)/2.0f), 0.0f);
        struct tuple point90 = tuple_point(-1.0f, 0.0f, 0.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate Z] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixShear()
{
        struct matrix t;
        struct tuple sp;
        struct tuple p = tuple_point(2.0f, 3.0f, 4.0f);

        // shear x in proportion to z
        t = matrix_shear(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        sp = tuple_point(6.0f, 3.0f, 4.0f);
        assert(tuple_equal(matrix_transform(t, p), sp) == 1);

        // shear y in proportion to x
        t = matrix_shear(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
        sp = tuple_point(2.0f, 5.0f, 4.0f);
        assert(tuple_equal(matrix_transform(t, p), sp) == 1);

        // shear y in proportion to z
        t = matrix_shear(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        sp = tuple_point(2.0f, 7.0f, 4.0f);
        assert(tuple_equal(matrix_transform(t, p), sp) == 1);
        
        // shear z in proportion to x
        t = matrix_shear(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        sp = tuple_point(2.0f, 3.0f, 6.0f);
        assert(tuple_equal(matrix_transform(t, p), sp) == 1);
        
        // shear z in proportion to y
        t = matrix_shear(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        sp = tuple_point(2.0f, 3.0f, 7.0f);
        assert(tuple_equal(matrix_transform(t, p), sp) == 1);

        fprintf(stdout, "[Matrix Shear] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixChain()
{
        struct tuple p = tuple_point(1.0f, 0.0f, 1.0f);
        struct matrix r_x = matrix_rotate_x(M_PI / 2.0f);
        struct matrix s = matrix_scale(5.0f, 5.0f, 5.0f);
        struct matrix t = matrix_translate(10.0f, 5.0f, 7.0f);

        struct tuple result = matrix_transform(r_x, p);
        assert(tuple_equal(result, tuple_point(1.0f, -1.0f, 0.0f)) == 1);

        result = matrix_transform(s, result);
        assert(tuple_equal(result, tuple_point(5.0f, -5.0f, 0.0f)) == 1);

        result = matrix_transform(t, result);
        assert(tuple_equal(result, tuple_point(15.0f, 0.0f, 7.0f)) == 1);

        struct matrix m = matrix_multiply(t,
                                matrix_multiply(s,
                                matrix_multiply(r_x, matrix_identity(4))));

        result = matrix_transform(m, p);
        assert(tuple_equal(result, tuple_point(15.0f, 0.0f, 7.0f)) == 1);
        // do it in one function
        printf("Pointers: %p, %p, %p\n", &r_x, &s, &t);
        transform(p, &r_x, &s, &t, &t, &t, NULL);

        fprintf(stdout, "[Matrix Chain] Complete, all tests pass!\n");
        return 1;
}
=======
>>>>>>> 0b60d153d339549e66c8caf34c255ff359f18ecf

        // reflection on x axis
        transform = matrix_scale(-1.0f, 1.0f, 1.0f);
        point = tuple_point(2.0f, 3.0f, 4.0f);
        scaled_point = tuple_point(-2.0f, 3.0f, 4.0f);
        assert(tuple_equal(matrix_transform(transform, point), scaled_point) == 1);

        fprintf(stdout, "[Matrix Scale] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateX()
{
        struct tuple point = tuple_point(0.0f, 1.0f, 0.0f);
        struct matrix rot45 = matrix_rotate_x(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_x(M_PI / 2.0f);

        struct tuple point45 = tuple_point(0.0f, (sqrt(2.0f)/2.0f),(sqrt(2.0f)/2.0f));
        struct tuple point90 = tuple_point(0.0f, 0.0f, 1.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate X] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateY()
{
        struct tuple point = tuple_point(0.0f, 0.0f, 1.0f);
        struct matrix rot45 = matrix_rotate_y(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_y(M_PI / 2.0f);

        struct tuple point45 = tuple_point((sqrt(2.0f)/2.0f), 0.0f, (sqrt(2.0f)/2.0f));
        struct tuple point90 = tuple_point(1.0f, 0.0f, 0.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate Y] Complete, all tests pass!\n");
        return 1;
}

int TST_MatrixRotateZ()
{
        struct tuple point = tuple_point(0.0f, 1.0f, 0.0f);
        struct matrix rot45 = matrix_rotate_z(M_PI / 4.0f);
        struct matrix rot90 = matrix_rotate_z(M_PI / 2.0f);

        struct tuple point45 = tuple_point(-1.0f * (sqrt(2.0f)/2.0f), (sqrt(2.0f)/2.0f), 0.0f);
        struct tuple point90 = tuple_point(-1.0f, 0.0f, 0.0f);

        assert(tuple_equal(matrix_transform(rot45, point), point45) == 1);
        assert(tuple_equal(matrix_transform(rot90, point), point90) == 1);

        fprintf(stdout, "[Matrix Rotate Z] Complete, all tests pass!\n");
        return 1;
}
int main()
{
        TST_MatrixNew();
        TST_MatrixEqual();
        TST_MatrixToString();
        TST_MatrixSetGet();
        TST_MatrixCopy();
        TST_MatrixMultiply();
        TST_MatrixTupleMultiply();
        TST_MatrixIdentity();
        TST_MatrixTranspose();
        TST_Matrix2Determinant();
        TST_Submatrix();
        TST_MatrixMinor();
        TST_MatrixCofactor();
        TST_MatrixDeterminant();
        TST_MatrixInvertible();
        TST_MatrixInverse();
        TST_MatrixTranslate();
        TST_MatrixScale();
        TST_MatrixRotateX();
        TST_MatrixRotateY();
        TST_MatrixRotateZ();
<<<<<<< HEAD
        TST_MatrixShear();
        TST_MatrixChain();
=======
>>>>>>> 0b60d153d339549e66c8caf34c255ff359f18ecf

        mem_free_all();

        return 0;
}
