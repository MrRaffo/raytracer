#include <stdio.h>

#include <geometry/tuple.h>
#include <geometry/gmaths.h>

// create a new tuple, initialised with given values
const tuple_t GEO_Tuple(const float x, const float y, const float z, const float w) {
        const tuple_t t = {x, y, z, w};
        return t;
}

// create a 'point' (a tuple where w == 1.0f)
const point_t GEO_Point(const float x, const float y, const float z)
{
        const tuple_t t = {x, y, z, 1.0f};
        return t;
}

// create a 'vector' (a tuple where w == 0.0f)
const vector_t GEO_Vector(const float x, const float y, const float z)
{       
        const tuple_t t = {x, y, z, 0.0f};
        return t;
}

// check if two tuples are equal to each other, return 1 if so, 0 if not
const int GEO_TupleEqual(const tuple_t tuple1, const tuple_t tuple2)
{
        if (!GEO_Equal(tuple1.w, tuple2.w)) { return 0; }
        if (!GEO_Equal(tuple1.x, tuple2.x)) { return 0; }
        if (!GEO_Equal(tuple1.y, tuple2.y)) { return 0; }
        if (!GEO_Equal(tuple1.z, tuple2.z)) { return 0; }
        return 1;
}

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int GEO_TupleCheckType(const tuple_t t)
{
        if (t.w == 0.0f) {
                return 0;
        } else if (t.w == 1.0f) {
                return 1;
        }

        return -1;
}
 
// print the tuple to the standard output
void GEO_PrintTuple(const tuple_t t)
{
        fprintf(stdout, "(%.2f, %.2f, %.2f, %.2f)\n",    
                t.x, t.y, t.z, t.w);
}

/* TUPLE OPERATIONS */
// add two tuples together and return a new tuple
const tuple_t GEO_TupleAdd(const tuple_t t1, const tuple_t t2)
{
        return GEO_Tuple(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w);
}

