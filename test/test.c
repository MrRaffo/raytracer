#include <stdio.h>
#include <geometry/tuple.h>

int main()
{
        struct tuple t = tuple_new(1.0f, 2.0f, 3.0f, 1.0f);
        struct tuple point = tuple_point(1.0f, 2.0f, 3.0f);
        printf("Tuple is: %f, %f, %f, %f\n", t.x, t.y, t.z, t.w);

        return 0;
}


