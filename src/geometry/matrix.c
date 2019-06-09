#include <stdio.h>

#include <geometry/matrix.h>
#include <geometry/tuple.h>
#include <geometry/gmaths.h>
#include <util/mem.h>
#include <util/log.h>

const struct matrix NULL_MATRIX = {0, 0, NULL};

/* Return a matrix, all elements initiated to 0.0f */
struct matrix matrix_new(const int r, const int c)
{
        float *ptr = (float *)mem_alloc(r * c * sizeof(float));
        
        // all elements should be 0.0f on creation
        for (int i = 0; i < r * c; i++) {
                *(ptr+i) = 0.0f;
        }
        
        struct matrix m = {r, c, ptr};

        return m;
}


/* Returns the identity matrix for a given dimension */
struct matrix matrix_identity(const int size)
{
        struct matrix m = matrix_new(size, size);
        for (int i = 0; i < size; i++) {
                matrix_set(m, i, i, 1.0f);
        }

        return m;
}


/* Returns 1 if matrix is the null matrix ({0, 0, NULL}), 0 if valid */
int matrix_is_null(const struct matrix m)
{
        if (m.row == 0 && m.col == 0 && m.matrix == NULL) return 1;
        return 0;
}

// all numbers formatted using %g, 11 char max
#define NUM_LEN 11
#define START "("
#define SEP ", "
#define END ")\n"

/* Return a matrix in a string */
char *matrix_to_string(const struct matrix m)
{

        // a line of the matrix will be returned as 
        // "(0000.000, 0000.000 ... )\n" for as many rows and cols as
        // needed, each line has opening and closing brackets (2), a comma and
        // space separator for each element in a row (2 * r - 1), and a newline
        int rowlength = 2 + 2 * (m.row - 1) + m.row * NUM_LEN + 1;
        // + 1 for '\0'
        int strlength = m.col * rowlength + 1;

        char *buf = (char *)mem_alloc(strlength);
        char *pos = buf;

        for (int i = 0; i < m.row * m.col; i++) {
                
                pos += sprintf(pos, "%s%g%s", 
                        (i % m.col == 0) ? START : "",  // start of a line
                        m.matrix[i], 
                        (i % m.col == m.col-1) ? END : SEP); // end of a line
        }

        *pos = '\0';    // make sure it's terminated
        *(buf+strlength-1) = '\0';      // I mean it...

        return buf;
}

/* output matrix data array, mostly for debugging */
char *matrix_to_string_raw(const struct matrix m)
{
        int mlen = m.row * m.col;
        char *buf = (char *)mem_alloc(1 + mlen * NUM_LEN + 3);
        char *ptr = buf;

        ptr += sprintf(ptr, "(");
        for (int i = 0; i < m.row * m.col - 1; i++) {
                ptr += sprintf(ptr, "%g, ", *(m.matrix+i));
        }

        ptr += sprintf(ptr, "%g)\n", *(m.matrix+m.row*m.col-1));
        *ptr = '\0';
        *(buf+mlen-1) = '\0';
        return buf;
}

/* OPERATIONS *
 * Unlike other structures in the library, this one operates on matrices in
 * place, a new one is not necessary created each time
 */

static int _check_valid_element(const struct matrix m, int r, int c)
{
        if (r < 0 || r >= m.row || c < 0 || c >= m.col) {
                return 0;
        }

        return 1;
}

/* Set the value of a row, col position, 0 if unable, 1 on success */
int matrix_set(struct matrix m, int r, int c, float value)
{
        if (!_check_valid_element(m, r, c)) {
                log_err("Bad matrix index! (%d, %d) requested in (%d, %d) matrix.",
                        r, c, m.row, m.col);
                return 0;
        }
        
        *(m.matrix+(r*m.col+c)) = value;
        return 1;
}

/* Retrieve a value from the matrix, returns 0.0f on bad index */
float matrix_get(const struct matrix m, int r, int c)
{
        if (!_check_valid_element(m, r, c)) {
                log_err("Bad matrix index! (%d, %d) requested in (%d, %d) matrix.",
                        r, c, m.row, m.col);
                return 0.0f;
        }

        return *(m.matrix+(r*m.col+c));
}

/* Check if two given matrices are equal, returns 1 if so, 0 otherwise */
int matrix_equal(const struct matrix m, const struct matrix n)
{
        if (m.row != n.row || m.col != n.col) {
                return 0;
        }
        
        for (int i = 0; i < m.row * m.col; i++) {
                if (!float_equal(*(m.matrix+i), *(n.matrix+i))) {
                        return 0;
                }
        }

        return 1;
}

/* Multiply two matrices if possible, return a new matrix if successful,
 * returns a null matrix {0, 0, NULL} on failure */
struct matrix matrix_multiply(const struct matrix m, const struct matrix n)
{
        // check if compatible
        if (m.col != n.row) {
                return NULL_MATRIX;
        }

        struct matrix result = matrix_new(m.row, n.col);
/*
        float value = 0.0f;
        for (int mr = 0; mr < m.row; mr++) {
                for (int nc = 0; nc < n.col; nc++) {
                        for (int i = 0; i < n.row; i++) {
                                value += matrix_get(m, mr, i) * matrix_get(n, i, nc);
                                printf("adding: %f * %f\t", matrix_get(m, mr, i), matrix_get(n, i, nc));
                                printf("total: %f\n", value);
                        }
                        printf("\n\n");
                        matrix_set(result, mr, nc, value);
                        value = 0.0f;
                }
        }
*/
        for (int r = 0; r < m.row; r++) {
                for (int c = 0; c < n.col; c++) {
                        float value = 0.0f;
                        for (int i = 0; i < m.col; i++) {
                                value += matrix_get(m, r, i) * matrix_get(n, i, c);
                        }
                        matrix_set(result, r, c, value);
                }
        }

        return result;
}

/* Return the 4 element tuple resulting in multiplying the given matrix and
 * tuple, rejects any matrix with row != 4 */
const struct tuple matrix_tuple_multiply(const struct matrix m, const struct tuple t)
{
        if (m.row != 4) {
                log_err("Invalid matrix passed! (%d x %d)\n", m.row, m.col);
                return tuple_new(0.0f, 0.0f, 0.0f, 0.0f);
        }

        float values[4];
        for (int i = 0; i < 4; i++) {
                values[i] = matrix_get(m, i, 0) * t.x + 
                            matrix_get(m, i, 1) * t.y +
                            matrix_get(m, i, 2) * t.z +
                            matrix_get(m, i, 3) * t.w;
        }

        return tuple_new(values[0], values[1], values[2], values[3]);
}
