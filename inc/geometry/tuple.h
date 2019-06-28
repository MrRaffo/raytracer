#ifndef __tuple_h__
#define __tuple_h__

#define TUPLE_VECTOR 0
#define TUPLE_POINT 1
#define TUPLE_NON_TYPE -1

struct tuple {
        double x;
        double y;
        double z;
        double w;
};

/* TUPLE CREATION */

// create a new tuple, initialised with given values
const struct tuple tuple_new(const double x, const double y, const double z, const double w);

// create a 'point' (a tuple where w == 1.0f)
const struct tuple tuple_point(const double x, const double y, const double z);

// create a 'vector' (a tuple where w == 0.0f)
const struct tuple tuple_vector(const double x, const double y, const double z);

// returns a zero tuple ({0, 0, 0, 0})
const struct tuple tuple_zero(void);

// returns the origin point ({0, 0, 0, 1})
const struct tuple tuple_origin(void);

// check if two tuples are equal to each other, return 1 if so, 0 if not
const int tuple_equal(const struct tuple t1, const struct tuple t2);

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int tuple_type(const struct tuple t);

// print the tuple to the standard output
void tuple_print(const struct tuple t);

/* return a string version of the tuple */
/* TODO - doesn't work, seg faults */
char *tuple_to_string(const struct tuple t);
 
/* TUPLE OPERATIONS */

// add two tuples together and return a new tuple
const struct tuple tuple_add(const struct tuple t1, const struct tuple t2);

// subtract tuple t2 from tuple t1 and return the result
const struct tuple tuple_subtract(const struct tuple t1, const struct tuple t2);

// get the negation of a tuple (tuple * -1) or, {0, 0, 0, 0,} - tuple
const struct tuple tuple_negate(const struct tuple t);

// multiply a vector by a scalar:
const struct tuple tuple_scale(const struct tuple t, const double f);

// divide a vector by a scalar:
// not commutative
const struct tuple tuple_divide(const struct tuple t, const double f);

// get the magnitude, or length, of a vector
const double vector_magnitude(const struct tuple t);

// return the normal (magnitude == 1.0f) of a given vector
const struct tuple vector_normal(const struct tuple v);

// return the dot product of two vectors (represents the angle between them)
const double vector_dot(const struct tuple v1, const struct tuple v2);

// return a new vector, the cross product of the two vectors passed
// Not commutative - returns a vector perpendicular to the 2 passed
const struct tuple vector_cross(const struct tuple v1, const struct tuple v2);
 
/* return the resulting vector after reflecting the given vector against the
 * given surface normal */
const struct tuple vector_reflect(struct tuple in, struct tuple normal);

#endif // __tuple_h__
