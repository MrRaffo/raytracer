#include <stdio.h>

#include <geometry/matrix.h>
#include <geometry/gmaths.h>
#include <util/mem.h>
#include <util/log.h>

/* Return a matrix, all elements initiated to 0.0f */
struct matrix matrix_new(const float r, const float c)
{
        float *ptr = (float *)mem_alloc(r * c * sizeof(float));
        
        // all elements should be 0.0f on creation
        for (int i = 0; i < r * c; i++) {
                *(ptr+i) = 0.0f;
        }
        
        struct matrix m = {r, c, ptr};

        return m;
}

/* Return a matrix in a string */
char *matrix_to_string(const struct matrix m)
{
        // all numbers formatted using %g, 11 char max
        #define NUM_LEN 11
        #define START "("
        #define SEP ", "
        #define END ")\n"
        // a line of the matrix will be returned as 
        // "(0000.00000000, 0000.00000000 ... )\n" for as many rows and cols as
        // needed, each line has opening and closing brackets (2), a comma and
        // space separator for each element in a row (2 * r - 1), and a newline
        int rowlength = 2 + 2 * (m.row - 1) + m.row * NUM_LEN + 1;
        // + 1 for '\0'
        int strlength = m.col * rowlength + 1;

        char *buf = (char *)mem_alloc(strlength);
        char *pos = buf;

        for (int i = 0; i < m.row * m.col; i++) {
                
                pos += sprintf(pos, "%s%g%s", 
                        (i % m.row == 0) ? START : "",  // start of a line
                        m.matrix[i], 
                        (i % m.row == m.row-1) ? END : SEP); // end of a line
        }

        *pos = '\0';    // make sure it's terminated
        *(buf+strlength-1) = '\0';      // I mean it...

        return buf;
}


/* OPERATIONS *
 * Unlike other structures in the library, this one operates on matrices in
 * place, a new one is not necessary created each time
 */

static int _check_valid_element(struct matrix m, int r, int c)
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
        
        *(m.matrix+(r*m.row+c)) = value;
        return 1;
}

/* Retrieve a value from the matrix, returns 0.0f on bad index */
float matrix_get(struct matrix m, int r, int c)
{
        if (!_check_valid_element(m, r, c)) {
                log_err("Bad matrix index! (%d, %d) requested in (%d, %d) matrix.",
                        r, c, m.row, m.col);
                return 0.0f;
        }

        return *(m.matrix+(r*m.row+c));
}

/* Check if two given matrices are equal, returns 1 if so, 0 otherwise */
int matrix_equal(struct matrix m, struct matrix n)
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
