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

int TST_TupleEqual()
{
        tuple_t t1 = GEO_Vector(1.0000004f, 3.0f, 4.0f);
        tuple_t t2 = GEO_Vector(1.00000f, 3.00000001f, 3.9999998f);
        tuple_t t3 = GEO_Point(1.0000004f, 3.0f, 4.0f);
        tuple_t t4 = GEO_Tuple(1.0000004f, 3.0f, 4.0f, 0.0f);
        tuple_t t5 = GEO_Point(3234.23f, 234.21f, 63690.234f);

        assert(GEO_TupleEqual(t1, t2) == 1);
        assert(GEO_TupleEqual(t1, t3) == 0);
        assert(GEO_TupleEqual(t1, t4) == 1);
        assert(GEO_TupleEqual(t3, t4) == 0);
        assert(GEO_TupleEqual(t2, t5) == 0);

        fprintf(stdout, "[Tuple Equality] All tests complete - pass!\n");

        return 1;
}

int TST_TupleAdd()
{
        tuple_t t1 = GEO_Tuple(1.0f, 2.0f, 3.0f, 0.0f);
        tuple_t t2 = GEO_Tuple(3.0f, 2.0f, 1.0f, 1.0f);
        tuple_t t3 = GEO_Point(4.0f, 4.0f, 4.0f);

        assert(GEO_TupleEqual(GEO_TupleAdd(t1, t2), t3));
        assert(!GEO_TupleEqual(GEO_TupleAdd(t1, t3), t2));

        fprintf(stdout, "[Tuple Add] All tests complete - pass!\n");

        return 1;
}

int TST_TupleSubtract()
{
        tuple_t p1 = GEO_Point(4.0f, 2.5f, 3.0f);
        tuple_t v1 = GEO_Vector(1.0f, 2.0f, 1.5f);
        tuple_t p2 = GEO_Point(3.0f, 2.5f, 1.0f);
        tuple_t t1 = GEO_Tuple(3.0f, 0.5f, 1.5f, 1.0f);

        assert(GEO_TupleEqual(GEO_TupleSubtract(p1, v1), t1));
        assert(GEO_TupleCheckType(GEO_TupleSubtract(p1, v1)) == GEO_POINT);
        assert(GEO_TupleCheckType(GEO_TupleSubtract(p1, p2)) == GEO_VECTOR);
        assert(GEO_TupleEqual(GEO_TupleSubtract(p2, p1), GEO_Tuple(-1.0f, 0.0f, -2.0f, 0.0f)));

        tuple_t mytup = {0.0f, 0.0f, 0.0f, 1.0f};

        fprintf(stdout, "[Tuple Subtract] All tests complete - pass!\n");

        return 1;
}

int TST_TupleNegate()
{
        tuple_t t1 = GEO_Tuple(1.0f, 2.0f, 3.0f, 4.0f);
        tuple_t t2 = GEO_Tuple(-1.0f, -2.0f, -3.0f, -4.0f);

        assert(GEO_TupleEqual(GEO_TupleNegate(t1), t2));
        assert(GEO_TupleEqual(GEO_TupleNegate(t2), t1));

        fprintf(stdout, "[Tuple Negate] All tests complete - pass!\n");

        return 1;
}

int TST_TupleMultiply()
{
        tuple_t t1 = GEO_Tuple(2.0f, 4.0f, 6.0f, 0.0f);
        tuple_t t2 = GEO_Tuple(4.0f, 8.0f, 12.0f, 0.0f);
        tuple_t t3 = GEO_Tuple(3.0f, 3.0f, 3.0f, 1.0f);
        tuple_t t4 = GEO_Tuple(9.0f, 9.0f, 9.0f, 3.0f);

        assert(GEO_TupleEqual(GEO_TupleMultiply(t1, 2.0f), t2));
        assert(GEO_TupleEqual(GEO_TupleMultiply(t3, 3.0f), t4));

        fprintf(stdout, "[Tuple Multiply] All tests complete - pass!\n");

        return 1;
}

int TST_TupleDivide()
{
        tuple_t t1 = GEO_Tuple(2.0f, 4.0f, 6.0f, 0.0f);
        tuple_t t2 = GEO_Tuple(4.0f, 8.0f, 12.0f, 0.0f);
        tuple_t t3 = GEO_Tuple(3.0f, 3.0f, 3.0f, 1.0f);
        tuple_t t4 = GEO_Tuple(9.0f, 9.0f, 9.0f, 3.0f);

        assert(GEO_TupleEqual(GEO_TupleDivide(t2, 2.0f), t1));
        assert(GEO_TupleEqual(GEO_TupleDivide(t4, 3.0f), t3));

        fprintf(stdout, "[Tuple Divide] All tests complete - pass!\n");

        return 1;
}

int main() 
{
        TST_TupleType();
        TST_TupleEqual();
        TST_TupleAdd();
        TST_TupleSubtract();
        TST_TupleNegate();
        TST_TupleMultiply();
        TST_TupleDivide();

        return 0;
}
