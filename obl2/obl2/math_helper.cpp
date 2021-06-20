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
