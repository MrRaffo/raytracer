#ifndef __tuple_h__
#define __tuple_h__

#define GEO_VECTOR 0
#define GEO_POINT 1

typedef struct tuple_s{
        float x;
        float y;
        float z;
        float w;
} tuple_t;

typedef tuple_t vector_t;
typedef tuple_t point_t;

// create a new tuple, initialised with given values
const tuple_t GEO_Tuple(const float x, const float y, const float z, const float w);

// create a 'point' (a tuple where w == 1.0f)
const point_t GEO_Point(const float x, const float y, const float z);

// create a 'vector' (a tuple where w == 0.0f)
const vector_t GEO_Vector(const float x, const float y, const float z);

// check if two tuples are equal to each other, return 1 if so, 0 if not
const int GEO_TupleEqual(const tuple_t tuple1, const tuple_t tuple2);

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int GEO_TupleCheckType(const tuple_t t);

// print the tuple to the standard output
void GEO_PrintTuple(const tuple_t t);
 
/* TUPLE OPERATIONS */
// add two tuples together and return a new tuple
const tuple_t GEO_TupleAdd(const tuple_t t1, const tuple_t t2);

      
#endif // __tuple_h__
