#include <handlers/vector_operations_handler.h>


void VectorOperationsHandler::vector_sum(Vector a, Vector b, Vector &c) {
    c.set_x(a.get_x() + b.get_x());
    c.set_y(a.get_y() + b.get_y());
    c.set_z(a.get_z() + b.get_z());
}

void VectorOperationsHandler::vector_substraction(Vector a, Vector b, Vector &c) {
    c.set_x(a.get_x() - b.get_x());
    c.set_y(a.get_y() - b.get_y());
    c.set_z(a.get_z() - b.get_z());
}

void VectorOperationsHandler::vector_scalar_product(float k, Vector a, Vector &b) {
    b.set_x(k * a.get_x());
    b.set_y(k * a.get_y());
    b.set_z(k * a.get_z());
}

float VectorOperationsHandler::vector_cross_product(Vector a, Vector b) {
    return(vector_magnitude(a) * vector_magnitude(b) * sin(vector_get_angle(a, b)));
}

float VectorOperationsHandler::vector_dot_product(Vector a, Vector b) {
    return((a.get_x() * b.get_x()) + (a.get_y() * b.get_y()) + (a.get_z() * b.get_z()));
}

float VectorOperationsHandler::vector_get_angle(Vector a, Vector b) {
    float product = vector_dot_product(a, b);
    float sq_mag_a = vector_squared_magnitude(a);
    float sq_mag_b = vector_squared_magnitude(b);
    return(acos(product/sqrt(sq_mag_a * sq_mag_b)));
}

void VectorOperationsHandler::vector_scalar_division(float k, Vector a, Vector &b) {
    b.set_x(a.get_x() / k);
    b.set_y(a.get_y() / k);
    b.set_z(a.get_z() / k);
}

void VectorOperationsHandler::vector_opposite(Vector a, Vector &b) {
    vector_scalar_product(-1, a, b);
}

float VectorOperationsHandler::vector_magnitude(Vector a) {
    return(sqrt(vector_squared_magnitude(a)));
}

float VectorOperationsHandler::vector_squared_magnitude(Vector a) {
    return(pow(a.get_x(), 2) + pow(a.get_y(), 2) + pow(a.get_z(), 2));
}

void VectorOperationsHandler::vector_normalize(Vector a, Vector &b) {
    float magnitude = vector_magnitude(a);
    if(magnitude == 0) {
        b.set_x(a.get_x());
        b.set_y(a.get_y());
        b.set_z(a.get_z());
    } else {
        b.set_x(a.get_x()/magnitude);
        b.set_y(a.get_y()/magnitude);
        b.set_z(a.get_z()/magnitude);
    }
}

void VectorOperationsHandler::vector_sym(Vector a, Vector b, Vector &c) {
    Vector norm_b;
    vector_normalize(b, norm_b);
    float product = vector_dot_product(a,  norm_b);
    c.set_x(2 * norm_b.get_x() * product - a.get_x());
    c.set_y(2 * norm_b.get_y() * product - a.get_y());
    c.set_z(2 * norm_b.get_z() * product - a.get_z());
}
