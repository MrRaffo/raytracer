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
const tuple_t GEO_Tuple(float x, float y, float z, float w);

// create a 'point' (a tuple where w == 1.0f)
const point_t GEO_Point(float x, float y, float z);

// create a 'vector' (a tuple where w == 0.0f)
const vector_t GEO_Vector(float x, float y, float z);

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int GEO_TupleCheckType(tuple_t t);

#endif // __tuple_h__
