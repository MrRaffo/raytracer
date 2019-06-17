#ifndef __matrix_h__
#define __matrix_h__

#include <geometry/tuple.h>

/*
 * Allows matrices of various sizes, row major
 */

struct matrix {
        int row;
        int col;
        double *matrix;
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

/* OPERATIONS */

/* return a copy of the given matrix */
struct matrix matrix_copy(const struct matrix m);

/* return a copy of the given matrix */
struct matrix matrix_copy(const struct matrix m);

/* Set the value of a row, col position, 0 if unable, 1 on success */
int matrix_set(struct matrix m, int r, int c, double value);

/* Retrieve a value from the matrix, returns 0.0f on bad index */
double matrix_get(const struct matrix m, int r, int c);

/* Check if two given matrices are equal, returns 1 if so, 0 otherwise */
int matrix_equal(const struct matrix m, const struct matrix n);

/* Multiply two matrices if possible, return a new matrix if successful,
 * returns a null matrix {0, 0, NULL} on failure */
struct matrix matrix_multiply(const struct matrix m, const struct matrix n);

/* Return the 4 element tuple resulting in multiplying the given matrix and
 * tuple, rejects any matrix with row != 4 */
const struct tuple matrix_transform(const struct matrix m, const struct tuple t);

/* takes a list of matrices and applies them all to a point 
 * applies matrices in reverse order, ie, intuitively, always applies
 * to the identity matrix so this need not be provided, last argument
 * must always be NULL */
const struct tuple transform(const struct tuple t, ...);

/* Return the transpose of the given matrix */
struct matrix matrix_transpose(const struct matrix m);

/* returns the determinant, matrix must be 2x2, returns 0 on fail */
double matrix_2determinant(const struct matrix m);

/* returns the determinant, matrix must be 3x3, returns 0 on fail */
double matrix_3determinant(const struct matrix m);

/* returns the minor of a 3x3 matrix at given point */
double matrix_minor(struct matrix m, int row, int col);

/* return the given matrix with the specified column and row removed
 * returns the null matrix on failure */
struct matrix submatrix(const struct matrix m, const int r, const int c);

/* return the cofactor of a given 3x3 matrix at the given element, 0.0f on fail */
double matrix_cofactor(const struct matrix m, const int r, const int c);

/* return the determinant of a matrix, 0.0f if unable for some reason */
double matrix_determinant(const struct matrix m);

/* test if a matrix is invertible, returns 0 if not, 1 if it is *
 * (a matrix is invertible if its determinant is non-zero
 */
const int matrix_invertible(const struct matrix m);

/* return the inverse of a matrix if it exists, returns null matrix on fail */
struct matrix matrix_inverse(const struct matrix m);

/* return a matrix that will translate by x, y, z */
struct matrix matrix_translate(const double x, const double y, const double z);

/* return a matrix to scale a tuple */
struct matrix matrix_scale(const double x, const double y, const double z);

/* return a matrix that will rotate around the x-axis, radians */
struct matrix matrix_rotate_x(const double radians);

/* return a matrix that will rotate around the y-axis, radians */
struct matrix matrix_rotate_y(const double radians);

/* return a matrix that will rotate around the z-axis, radians */
struct matrix matrix_rotate_z(const double radians);

/* return a matrix that shears */
struct matrix matrix_shear(const double xy, const double xz, const double yx, const double yz, const double zx, const double zy);

#endif // __matrix_h__
