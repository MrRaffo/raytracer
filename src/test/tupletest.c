#include <stdio.h>
#include <math.h>

#include <geometry/tuple.h>
#include <geometry/g_maths.h>
#include <util/log.h>

#include <assert.h>

int TST_TupleType()
{
        struct tuple vec = tuple_vector(1.0f, 2.0f, 3.0f);
        struct tuple point = tuple_point(3.0f, 4.0f, 5.0f);
        struct tuple invalid = tuple_new(2.0f, 2.0f, 2.0f, 2.0f);

        assert(tuple_type(vec) == TUPLE_VECTOR);
        assert(tuple_type(point) == TUPLE_POINT);
        assert(tuple_type(invalid) < 0);

        log_msg("[Tuple Type] All tests complete - pass!");

        return 1;
}

int TST_TuplePrint()
{
        struct tuple vec = tuple_vector(1.0f, 2.0f, 3.0f);
        struct tuple point = tuple_point(3.0f, 4.0f, 5.0f);
        struct tuple invalid = tuple_new(2.0f, 2.0f, 2.0f, 2.0f);

        log_msg("Demonstrating tuple print");
        tuple_print(vec);
        tuple_print(point);
        tuple_print(invalid);

        return 1;
}

int TST_TupleEqual()
{
        struct tuple t1 = tuple_vector(1.0000004f, 3.0f, 4.0f);
        struct tuple t2 = tuple_vector(1.00000f, 3.00000001f, 3.9999998f);
        struct tuple t3 = tuple_point(1.0000004f, 3.0f, 4.0f);
        struct tuple t4 = tuple_new(1.0000004f, 3.0f, 4.0f, 0.0f);
        struct tuple t5 = tuple_point(3234.23f, 234.21f, 63690.234f);

        assert(tuple_equal(t1, t2) == 1);
        assert(tuple_equal(t1, t3) == 0);
        assert(tuple_equal(t1, t4) == 1);
        assert(tuple_equal(t3, t4) == 0);
        assert(tuple_equal(t2, t5) == 0);

        log_msg("[Tuple Equal] All tests complete - pass!");

        return 1;
}

int TST_TupleAdd()
{
        struct tuple t1 = tuple_new(1.0f, 2.0f, 3.0f, 0.0f);
        struct tuple t2 = tuple_new(3.0f, 2.0f, 1.0f, 1.0f);
        struct tuple t3 = tuple_point(4.0f, 4.0f, 4.0f);

        assert(tuple_equal(tuple_add(t1, t2), t3));
        assert(!tuple_equal(tuple_add(t1, t3), t2));

        log_msg("[Tuple Add] All tests complete - pass!");

        return 1;
}

int TST_TupleSubtract()
{
        struct tuple p1 = tuple_point(4.0f, 2.5f, 3.0f);
        struct tuple v1 = tuple_vector(1.0f, 2.0f, 1.5f);
        struct tuple p2 = tuple_point(3.0f, 2.5f, 1.0f);
        struct tuple t1 = tuple_new(3.0f, 0.5f, 1.5f, 1.0f);

        assert(tuple_equal(tuple_subtract(p1, v1), t1));
        assert(tuple_type(tuple_subtract(p1, v1)) == TUPLE_POINT);
        assert(tuple_type(tuple_subtract(p1, p2)) == TUPLE_VECTOR);
        assert(tuple_equal(tuple_subtract(p2, p1), tuple_new(-1.0f, 0.0f, -2.0f, 0.0f)));

        log_msg("[Tuple Subtract] All tests complete - pass!");

        return 1;
}

int TST_TupleNegate()
{
        struct tuple t1 = tuple_new(1.0f, 2.0f, 3.0f, 4.0f);
        struct tuple t2 = tuple_new(-1.0f, -2.0f, -3.0f, -4.0f);

        assert(tuple_equal(tuple_negate(t1), t2));
        assert(tuple_equal(tuple_negate(t2), t1));

        log_msg("[Tuple Negate] All tests complete - pass!");

        return 1;
}

int TST_TupleMultiply()
{
        struct tuple t1 = tuple_new(2.0f, 4.0f, 6.0f, 0.0f);
        struct tuple t2 = tuple_new(4.0f, 8.0f, 12.0f, 0.0f);
        struct tuple t3 = tuple_new(3.0f, 3.0f, 3.0f, 1.0f);
        struct tuple t4 = tuple_new(9.0f, 9.0f, 9.0f, 3.0f);

        assert(tuple_equal(tuple_scale(t1, 2.0f), t2));
        assert(tuple_equal(tuple_scale(t3, 3.0f), t4));

        log_msg("[Tuple Multiply] All tests complete - pass!");

        return 1;
}

int TST_TupleDivide()
{
        struct tuple t1 = tuple_new(2.0f, 4.0f, 6.0f, 0.0f);
        struct tuple t2 = tuple_new(4.0f, 8.0f, 12.0f, 0.0f);
        struct tuple t3 = tuple_new(3.0f, 3.0f, 3.0f, 1.0f);
        struct tuple t4 = tuple_new(9.0f, 9.0f, 9.0f, 3.0f);

        assert(tuple_equal(tuple_divide(t2, 2.0f), t1));
        assert(tuple_equal(tuple_divide(t4, 3.0f), t3));

        log_msg("[Tuple Divide] All tests complete - pass!");

        return 1;
}

int TST_VectorMagnitude()
{
        struct tuple v1 = tuple_vector(1.0f, 0.0f, 0.0f);
        struct tuple v2 = tuple_vector(0.0f, 1.0f, 0.0f);
        struct tuple v3 = tuple_vector(0.0f, 0.0f, 1.0f);

        struct tuple v4 = tuple_vector(2.0f, 3.0f, 4.0f);
        struct tuple v5 = tuple_vector(1.0f, 2.0f, 3.0f);

        assert(double_equal(vector_magnitude(v1), 1.0f));
        assert(double_equal(vector_magnitude(v2), 1.0f));
        assert(double_equal(vector_magnitude(v3), 1.0f));
        
        assert(double_equal(vector_magnitude(v4), 5.3851648f));
        assert(double_equal(vector_magnitude(v5), 3.7416573f));

        log_msg("[Vector Magnitude] - All tests complete - pass!");

        return 1;
}

int TST_VectorNormal()
{
        struct tuple v1 = tuple_vector(1.5f, 5.0f, 0.0f);
        struct tuple v2 = tuple_vector(0.2f, 1.8f, 6.2f);
        struct tuple v3 = tuple_vector(-8.65f, -6.234f, 1.0f);
        struct tuple v4 = tuple_vector(2.0f, 3.0f, 4.0f);
        struct tuple v5 = tuple_vector(1.0f, 2.0f, 3.0f);
        struct tuple v6 = tuple_vector(45.3f, -90.123f, 3.3f);
        struct tuple v7 = tuple_vector(0.0f, 0.0f, 0.0f);       // special case

        assert(double_equal(vector_magnitude(vector_normal(v1)), 1.0f) == 1);
        assert(double_equal(vector_magnitude(vector_normal(v2)), 1.0f) == 1);
        assert(double_equal(vector_magnitude(vector_normal(v3)), 1.0f) == 1);
        assert(double_equal(vector_magnitude(vector_normal(v4)), 1.0f) == 1);
        assert(double_equal(vector_magnitude(vector_normal(v5)), 1.0f) == 1);
        assert(double_equal(vector_magnitude(vector_normal(v6)), 1.0f) == 1);
        vector_magnitude(vector_normal(v7));    // just don't break...
        
        log_msg("[Vector Normal] All tests complete - pass!");

        return 1;
}

int TST_VectorDot()
{
        struct tuple v1 = tuple_vector(1.0f, 2.0f, 3.0f);
        struct tuple v2 = tuple_vector(2.0f, 3.0f, 4.0f);
        struct tuple v3 = tuple_vector(3.0f, -3.0f, 3.0f);

        assert(double_equal(vector_dot(v1, v2), 20.0f) == 1);
        assert(double_equal(vector_dot(v1, v3), 6.0f) == 1);
        assert(double_equal(vector_dot(v2, v3), 9.0f) == 1);
        assert(double_equal(vector_dot(v3, v3), 27.0f) == 1);

        log_msg("[Vector Dot] All test complete - pass!");

        return 1;
}

int TST_VectorCross()
{
        struct tuple a = tuple_vector(1.0f, 0.0f, 0.0f);
        struct tuple b = tuple_vector(0.0f, 1.0f, 0.0f);
        struct tuple c = tuple_vector(0.0f, 0.0f, 1.0f);

        assert(tuple_equal(vector_cross(a, b), c) == 1);
        assert(tuple_equal(vector_cross(b, a), tuple_negate(c)) == 1);
        assert(tuple_equal(vector_cross(c, a), b) == 1);
        assert(tuple_equal(vector_cross(b, c), a) == 1);

        log_msg("[Vector Cross] All test complete - pass!");

        return 1;
}

// test reflection of vector against given surface normal
int TST_VectorReflect()
{
        struct tuple vec = tuple_vector(1.0, -1.0, 0.0);
        struct tuple nor = tuple_vector(0.0, 1.0, 0.0);
        struct tuple ref = vector_reflect(vec, nor);

        assert(tuple_equal(ref, tuple_vector(1.0, 1.0, 0.0)) == 1);

        // reflect vertical drop against 45 degree incline should produce
        // horizontal vector
        vec = tuple_vector(0.0, -1.0, 0.0);
        nor = tuple_vector(sqrt(2.0)/2.0, sqrt(2.0)/2.0, 0.0);
        ref = vector_reflect(vec, nor);

        assert(tuple_equal(ref, tuple_vector(1.0, 0.0, 0.0)) == 1);

        log_msg("[Vector Reflect] Complete, all tests pass!");
        
        return 1;
}

int main() 
{
        TST_TupleType();
        TST_TuplePrint();
        TST_TupleEqual();
        TST_TupleAdd();
        TST_TupleSubtract();
        TST_TupleNegate();
        TST_TupleMultiply();
        TST_TupleDivide();
        TST_VectorMagnitude();
        TST_VectorNormal();
        TST_VectorDot();
        TST_VectorCross();
        TST_VectorReflect();
        
        return 0;
}
