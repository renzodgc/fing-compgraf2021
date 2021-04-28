// HEADERS
// -----------------------------------------------------------------------------------
#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

position normalize_vector(position pos) {
	double magnitude = sqrt(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2));
	if (magnitude == 0.) { return { 0.f, 0.f, 0.f }; }
	return { (float)(pos.x / magnitude), (float)(pos.y / magnitude), (float)(pos.z / magnitude) };
}

position cross_product_vector(position a, position b) {
	return {
		a.y * b.z - a.z * b.y,
		-(a.x * b.z - a.z * b.x),
		a.x * b.y - a.y * b.x
	};
}

float degree_to_radian(float degree) {
	float pi = 3.14159265359f;
	return(degree * (pi / 180.f));
}
