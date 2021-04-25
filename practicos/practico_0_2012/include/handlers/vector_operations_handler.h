#ifndef VECTOR_OPERATIONS_HANDLER_H
#define VECTOR_OPERATIONS_HANDLER_H

#include <models/vector.h>
#include <cmath>

class VectorOperationsHandler {
    public:
        VectorOperationsHandler(){}
        ~VectorOperationsHandler(){}
        static void vector_sum(Vector a, Vector b, Vector &c);
        static void vector_substraction(Vector a, Vector b, Vector &c);
        static void vector_scalar_product(float k, Vector a, Vector &b);
        static float vector_cross_product(Vector a, Vector b);
        static float vector_dot_product(Vector a, Vector b);
        static float vector_get_angle(Vector a, Vector b);
        static void vector_scalar_division(float k, Vector a, Vector &b);
        static void vector_opposite(Vector a, Vector &b);
        static float vector_squared_magnitude(Vector a);
        static float vector_magnitude(Vector a);
        static void vector_normalize(Vector a, Vector &b);
        static void vector_sym(Vector a, Vector b, Vector &c);
};

#endif
