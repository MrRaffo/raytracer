#include <stdio.h>
#include <geometry/tuple.h>

int main()
{
        tuple_t tuple = GEO_Tuple(1.0f, 2.0f, 3.0f, 1.0f);
        tuple_t point = GEO_Point(1.0f, 2.0f, 3.0f);
        printf("Tuple is: %f, %f, %f, %f\n", tuple.x, tuple.y, tuple.z, tuple.w);

        return 0;
}


