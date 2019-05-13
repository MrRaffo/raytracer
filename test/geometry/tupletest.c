#include <stdio.h>
#include <geometry/tuple.h>
#include <assert.h>

int TST_TupleType()
{
        vector_t vec = GEO_Vector(1.0f, 2.0f, 3.0f);
        point_t point = GEO_Point(3.0f, 4.0f, 5.0f);
        tuple_t invalid = GEO_Tuple(2.0f, 2.0f, 2.0f, 2.0f);

        assert(GEO_TupleCheckType(vec) == GEO_VECTOR);
        assert(GEO_TupleCheckType(point) == GEO_POINT);
        assert(GEO_TupleCheckType(invalid) < 0);

        fprintf(stdout, "[Tuple Type] All tests complete - pass!\n");

        return 1;
}

int main() {
        
        TST_TupleType();

        return 0;
}
