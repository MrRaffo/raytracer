#include <stdio.h>

#include <geometry/tuple.h>

// create a new tuple, initialised with given values
const tuple_t GEO_Tuple(float x, float y, float z, float w) {
        const tuple_t t = {x, y, z, w};
        return t;
}

// create a 'point' (a tuple where w == 1.0f)
const point_t GEO_Point(float x, float y, float z)
{
        const tuple_t t = {x, y, z, 1.0f};
        return t;
}

// create a 'vector' (a tuple where w == 0.0f)
const vector_t GEO_Vector(float x, float y, float z)
{       
        const tuple_t t = {x, y, z, 0.0f};
        return t;
}

// return 1 if tuple is a point, 0 if a vector, -1 if not valid
const int GEO_TupleCheckType(tuple_t t)
{
        if (t.w == 0.0f) {
                return 0;
        } else if (t.w == 1.0f) {
                return 1;
        }

        return -1;
}
 
// print the tuple to the standard output
void GEO_PrintTuple(tuple_t t)
{
        fprintf(stdout, "(%.2f, %.2f, %.2f, %.2f)\n",    
                t.x, t.y, t.z, t.w);
}
