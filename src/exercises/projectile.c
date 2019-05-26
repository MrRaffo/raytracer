/*
 * Exercise from chapter 1, 'Putting it all together', using
 * vectors and points to simulate a moving object under the
 * influence of gravity and wind
 */

 #include <stdio.h>

 #include <geometry/tuple.h>
 
struct environment {
        struct tuple gravity;
        struct tuple wind;
};

struct projectile {
        struct tuple position;
        struct tuple velocity;
};


int main()
{
        struct environment env = { tuple_vector(0.0f, -0.1f, 0.0f), tuple_vector(0.003f, 0.0f, 0.0f) };
        struct projectile proj = { tuple_point(0.0f, 1.0f, 0.0f), tuple_vector(2.4f, 0.0f, 0.0f) };

        while (proj.position.y > 0.0f) {
                proj.position = tuple_add(proj.position, proj.velocity);
                proj.velocity = tuple_add(proj.velocity, tuple_add(env.gravity, env.wind));

                tuple_print(proj.position);
        }

        return 0;
}
