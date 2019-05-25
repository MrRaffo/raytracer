#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/gmaths.h>

// create a new tuple, initialised with given values
const struct tuple tuple_new(const float x, const float y, const float z, const float w) {
        const struct tuple t = {x, y, z, w};
        return t;
}

// create a 'point' (a tuple where w == 1.0f)
const struct tuple tuple_point(const float x, const float y, const float z)
{
        const struct tuple t = {x, y, z, 1.0f};
        return t;
}

// create a 'vector' (a tuple where w == 0.0f)
const struct tuple tuple_vector(const float x, const float y, const float z)
{       
        const struct tuple t = {x, y, z, 0.0f};
        return t;
}

// returns a zero tuple ({0, 0, 0, 0})
const struct tuple tuple_zero(void)
{
        return tuple_new(0.0f, 0.0f, 0.0f, 0.0f);
}

// check if two tuples are equal to each other, return 1 if so, 0 if not
const int tuple_equal(const struct tuple t1, const struct tuple t2)
{
        if (!float_equal(t1.w, t2.w)) { return 0; }
        if (!float_equal(t1.x, t2.x)) { return 0; }
        if (!float_equal(t1.y, t2.y)) { return 0; }
        if (!float_equal(t1.z, t2.z)) { return 0; }
        return 1;
}

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int tuple_type(const struct tuple t)
{
        if (t.w == 0.0f) {
                return TUPLE_VECTOR;
        } else if (t.w == 1.0f) {
                return TUPLE_POINT;
        }

        return TUPLE_NON_TYPE;
}
 
// print the tuple to the standard output
void tuple_print(const struct tuple t)
{
        fprintf(stdout, "(%.2f, %.2f, %.2f, %.2f)\n",    
                t.x, t.y, t.z, t.w);
}
// get the magnitude, or length, of a vector
const float tuple_magnitude(const struct tuple t);

/* TUPLE OPERATIONS */
// add two tuples together and return a new tuple
const struct tuple tuple_add(const struct tuple t1, const struct tuple t2)
{
        return tuple_new(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w);
}

// subtract tuple t2 from tuple t1 and return the result
const struct tuple tuple_subtract(const struct tuple t1, const struct tuple t2)
{
        return tuple_new(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w);
}
 
// get the negation of a tuple (tuple * -1) or, {0, 0, 0, 0,} - tuple
const struct tuple tuple_negate(const struct tuple t)
{
        return tuple_new(0.0f - t.x, 0.0f - t.y, 0.0f - t.z, 0.0f - t.w);
}

// multiply a vector by a scalar:
const struct tuple tuple_scale(const struct tuple t, const float f)
{
        return tuple_new(t.x * f, t.y * f, t.z * f, t.w * f);
}

// divide a vector by a scalar:
const struct tuple tuple_divide(const struct tuple t, const float f)
{
        return tuple_new(t.x / f, t.y / f, t.z / f, t.w / f);
}

// get the magnitude, or length, of a vector
const float vector_magnitude(const struct tuple vec)
{
        float m = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
        return sqrtf(m);
}

// return the normal (magnitude == 1.0f) of a given vector
const struct tuple vector_normal(const struct tuple v)
{
        float mag = vector_magnitude(v);
        if (mag == 0.0f) return v;
        return tuple_vector(v.x / mag, v.y / mag, v.z / mag);
}

// return the dot product of two vectors (represents the angle between them)
const float vector_dot(const struct tuple v1, const struct tuple v2)
{
       return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// return a new vector, the cross product of the two vectors passed
// not commutative
const struct tuple vector_cross(const struct tuple v1, const struct tuple v2)
{
        return tuple_vector(v1.y * v2.z - v1.z * v2.y,
                            v1.z * v2.x - v1.x * v2.z,
                            v1.x * v2.y - v1.y * v2.x);
}
