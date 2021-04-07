// Global dependencies
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cmath>

// Local dependencies
#include <handlers/vector_operations_handler.h>
#include <models/vector.h>
#include <handlers/log_handler.h>
#include <const.h>

void print_vector(Vector a) {
    printf("(%f, %f, %f)", a.get_x(), a.get_y(), a.get_z());
}

// Main method
int main(int argc, char** argv){
    // Variables
    float k = 5;
    float k_zero = 0;
    float k_one = 1;
    float result;
    Vector a, b, c, d, i, zero, vector_result;
    zero.set_x(0); zero.set_y(0); zero.set_z(0); // (0,0,0)
    i.set_x(1); i.set_y(1); i.set_z(1); // (1,1,1)

    a.set_x(1); a.set_y(0); a.set_z(1); // (1,0,1)
    b.set_x(2); b.set_y(1); b.set_z(2); // (2,1,2)
    c.set_x(0); c.set_y(3); c.set_z(0); // (0,3,0)

    log_msg("Vector Sum");
    VectorOperationsHandler::vector_sum(a, zero, vector_result);
    printf("a + zero = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sum(a, i, vector_result);
    printf("a + i = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sum(a, b, vector_result);
    printf("a + b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sum(b, c, vector_result);
    printf("b + c = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sum(c, a, vector_result);
    printf("c + a = ");
    print_vector(vector_result);


    log_msg("Vector Substraction");
    VectorOperationsHandler::vector_substraction(a, zero, vector_result);
    printf("a - zero = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_substraction(a, i, vector_result);
    printf("a - i = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_substraction(a, b, vector_result);
    printf("a - b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_substraction(b, c, vector_result);
    printf("b - c = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_substraction(c, a, vector_result);
    printf("c - a = ");
    print_vector(vector_result);


    log_msg("Vector Scalar Product");
    VectorOperationsHandler::vector_scalar_product(k_zero, a, vector_result);
    printf("k_zero * a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_product(k_one, a, vector_result);
    printf("k_one * a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_product(k, a, vector_result);
    printf("k * a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_product(k_zero, b, vector_result);
    printf("k * b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_product(k_zero, c, vector_result);
    printf("k * c = ");
    print_vector(vector_result);


    log_msg("Vector Cross Product");
    printf("a x zero = %f", VectorOperationsHandler::vector_cross_product(a, zero));
    printf("a x i = %f", VectorOperationsHandler::vector_cross_product(a, i));
    printf("a x b = %f", VectorOperationsHandler::vector_cross_product(a, b));
    printf("b x c = %f", VectorOperationsHandler::vector_cross_product(b, c));
    printf("c x a = %f", VectorOperationsHandler::vector_cross_product(c, a));


    log_msg("Vector Dot Product");
    printf("a . zero = %f", VectorOperationsHandler::vector_dot_product(a, zero));
    printf("a . i = %f", VectorOperationsHandler::vector_dot_product(a, i));
    printf("a . b = %f", VectorOperationsHandler::vector_dot_product(a, b));
    printf("b . c = %f", VectorOperationsHandler::vector_dot_product(b, c));
    printf("c . a = %f", VectorOperationsHandler::vector_dot_product(c, a));


    log_msg("Vector Get Angle");
    printf("a ^ zero = %f", VectorOperationsHandler::vector_get_angle(a, zero));
    printf("a ^ i = %f", VectorOperationsHandler::vector_get_angle(a, i));
    printf("a ^ b = %f", VectorOperationsHandler::vector_get_angle(a, b));
    printf("b ^ c = %f", VectorOperationsHandler::vector_get_angle(b, c));
    printf("c ^ a = %f", VectorOperationsHandler::vector_get_angle(c, a));


    log_msg("Vector Scalar Division");
    VectorOperationsHandler::vector_scalar_division(k_zero, a, vector_result);
    printf("k_zero / a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_division(k_one, a, vector_result);
    printf("k_one / a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_division(k, a, vector_result);
    printf("k / a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_division(k_zero, b, vector_result);
    printf("k / b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_scalar_division(k_zero, c, vector_result);
    printf("k / c = ");
    print_vector(vector_result);


    log_msg("Vector Opposite");
    VectorOperationsHandler::vector_opposite(zero, vector_result);
    printf("-zero = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_opposite(i, vector_result);
    printf("-i = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_opposite(a, vector_result);
    printf("-a = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_opposite(b, vector_result);
    printf("-b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_opposite(c, vector_result);
    printf("-c = ");
    print_vector(vector_result);


    log_msg("Vector Squared Magnitude");
    result = VectorOperationsHandler::vector_squared_magnitude(a);
    printf("manitude(zero)^2 = %f", VectorOperationsHandler::vector_squared_magnitude(zero));
    printf("manitude(i)^2 = %f", VectorOperationsHandler::vector_squared_magnitude(i));
    printf("manitude(a)^2 = %f", VectorOperationsHandler::vector_squared_magnitude(a));
    printf("manitude(b)^2 = %f", VectorOperationsHandler::vector_squared_magnitude(b));
    printf("manitude(c)^2 = %f", VectorOperationsHandler::vector_squared_magnitude(c));


    log_msg("Vector Magnitude");
    printf("manitude(zero)^2 = %f", VectorOperationsHandler::vector_magnitude(zero));
    printf("manitude(i)^2 = %f", VectorOperationsHandler::vector_magnitude(i));
    printf("manitude(a)^2 = %f", VectorOperationsHandler::vector_magnitude(a));
    printf("manitude(b)^2 = %f", VectorOperationsHandler::vector_magnitude(b));
    printf("manitude(c)^2 = %f", VectorOperationsHandler::vector_magnitude(c));

    log_msg("Vector Normalize");
    VectorOperationsHandler::vector_normalize(zero, vector_result);
    printf("norm(zero) = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_normalize(i, vector_result);
    printf("norm(i) = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_normalize(a, vector_result);
    printf("norm(a) = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_normalize(b, vector_result);
    printf("norm(b) = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_normalize(c, vector_result);
    printf("norm(c) = ");
    print_vector(vector_result);


    log_msg("Vector Sym");
    VectorOperationsHandler::vector_sym(a, zero, vector_result);
    printf("a sym zero = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sym(a, i, vector_result);
    printf("a sym i = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sym(a, b, vector_result);
    printf("a sym b = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sym(b, c, vector_result);
    printf("b sym c = ");
    print_vector(vector_result);
    VectorOperationsHandler::vector_sym(c, a, vector_result);
    printf("c sym a = ");
    print_vector(vector_result);

	return OK;
}