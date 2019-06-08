#ifndef __matrix_h__
#define __matrix_h__

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
struct matrix matrix_new(const float r, const float c);

/* Return a matrix in a string */
char *matrix_to_string(const struct matrix m);

/* OPERATIONS *
 * Unlike other structures in the library, this one operates on matrices in
 * place, a new one is not necessary created each time
 */

/* Set the value of a row, col position, 0 if unable, 1 on success */
int matrix_set(struct matrix m, int r, int c, float value);

/* Retrieve a value from the matrix, returns 0.0f on bad index */
float matrix_get(struct matrix m, int r, int c);

/* Check if two given matrices are equal, returns 1 if so, 0 otherwise */
int matrix_equal(struct matrix m, struct matrix n);

#endif // __matrix_h__
