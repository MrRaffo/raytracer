#include <stdio.h>

#include <geometry/tuple.h>
#include <geometry/matrix.h>
#include <util/mem.h>
#include <util/log.h>

void invert_identity()
{
        struct matrix id = matrix_identity(4);
        printf("Identity:\n%s\n", matrix_to_string(id));
        printf("Inverted:\n%s\n", matrix_to_string(matrix_inverse(id)));
}

void inverse_multiply()
{
        struct matrix m = matrix_new(4, 4);
        float data[] = {-5.0f, 2.0f, 6.0f, -8.0f,
                          1.0f, -5.0f, 1.0f, 8.0f,
                          7.0f, 7.0f, -6.0f, -7.0f,
                          1.0f, -3.0f, 7.0f, 4.0f};
       
        m.matrix = data;

        printf("Matrix:\n%s\n", matrix_to_string(m));
        printf("Inverse:\n%s\n", matrix_to_string(matrix_inverse(m)));
        printf("Product:\n%s\n", matrix_to_string(matrix_multiply(matrix_inverse(m), m)));
}

void inverse_transpose()
{
        struct matrix m = matrix_new(4, 4);
        float data[] = {-5.0f, 2.0f, 6.0f, -8.0f,
                          1.0f, -5.0f, 1.0f, 8.0f,
                          7.0f, 7.0f, -6.0f, -7.0f,
                          1.0f, -3.0f, 7.0f, 4.0f};
        
        m.matrix = data;

        struct matrix t = matrix_transpose(m);
        struct matrix i = matrix_inverse(m);
        
        printf("Matrix:\n%s\n", matrix_to_string(m));
        printf("Transpose:\n%s\n", matrix_to_string(t));
        printf("Inverse of Transpose:\n%s\n", matrix_to_string(matrix_inverse(t)));
        printf("Transpose of Inverse:\n%s\n", matrix_to_string(matrix_transpose(i)));
}

void tuple_multiply()
{
        struct tuple point = tuple_new(1.0f, 2.0f, 3.0f, 1.0f);
        struct matrix m = matrix_identity(4);
        matrix_set(m, 2, 1, 31.0f);

        //printf("Tuple:\n%s\nMatrix:\n%s\n\nProduct:\n%s\n",
        //        tuple_to_string(point),
        //        matrix_to_string(m),
        //        tuple_to_string(matrix_tuple_multiply(m, point)));
        tuple_print(matrix_tuple_multiply(m, point));
}

int main()
{
        printf("INVERT IDENTITY MATRIX\n");
        invert_identity();
        printf("\n\n");

        printf("MULTIPLY BY INVERSE\n");
        inverse_multiply();
        printf("\n\n");

        printf("INVERSE TRANSPOSE ASSOCIATIVITY\n");
        inverse_transpose();
        printf("\n\n");

        printf("MULITPLY BY TUPLE\n");
        tuple_multiply();
        printf("\n\n");

        mem_free_all();

        return 0;
}
