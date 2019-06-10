#ifndef __matrix_h__
#define __matrix_h__

#include <geometry/tuple.h>

/*
 * Allows matrices of various sizes, row major
 */

struct matrix {
        int row;
        int col;
        float *matrix;
};

/* CREATION */

/* Return a matrix, all elements initiated to 0.0f */
struct matrix matrix_new(const int r, const int c);

/* Returns the identity matrix for a given dimension */
struct matrix matrix_identity(const int size);

/* Returns 1 if matrix is the null matrix ({0, 0, NULL}), 0 if valid */
int matrix_is_null(const struct matrix m);

/* Return a matrix in a string */
char *matrix_to_string(const struct matrix m);

/* output matrix data array, mostly for debugging */
char *matrix_to_string_raw(const struct matrix m);

/* OPERATIONS *
 * Unlike other structures in the library, this one operates on matrices in
 * place, a new one is not necessary created each time
 */

/* Set the value of a row, col position, 0 if unable, 1 on success */
int matrix_set(struct matrix m, int r, int c, float value);

/* Retrieve a value from the matrix, returns 0.0f on bad index */
float matrix_get(const struct matrix m, int r, int c);

/* Check if two given matrices are equal, returns 1 if so, 0 otherwise */
int matrix_equal(const struct matrix m, const struct matrix n);

/* Multiply two matrices if possible, return a new matrix if successful,
 * returns a null matrix {0, 0, NULL} on failure */
struct matrix matrix_multiply(const struct matrix m, const struct matrix n);

/* Return the 4 element tuple resulting in multiplying the given matrix and
 * tuple, rejects any matrix with row != 4 */
const struct tuple matrix_tuple_multiply(const struct matrix m, const struct tuple t);

/* Return the transpose of the given matrix */
struct matrix matrix_transpose(const struct matrix m);

#endif // __matrix_h__
