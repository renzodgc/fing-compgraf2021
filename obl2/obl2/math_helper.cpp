// HEADERS
// -----------------------------------------------------------------------------------
#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

Color add_colors(Color a, Color b) {
	return { (a.red + b.red), (a.green + b.green), (a.blue + b.blue) };
}

Color multiply_colors(Color a, Color b) {
	return { (a.red * b.red), (a.green * b.green), (a.blue * b.blue) };
}

Color scale_color(Color a, float k) {
	return { (a.red * k), (a.green * k), (a.blue * k) };
}

float determinant3x3(Vector a, Vector b, Vector c) {
	float result = a.x * ((b.y * c.z) - (b.z * c.y));
	result -= a.y * ((b.x * c.z) - (b.z * c.x));
	result += a.z * ((b.x * c.y) - (b.y * c.x));
	return result;
}
