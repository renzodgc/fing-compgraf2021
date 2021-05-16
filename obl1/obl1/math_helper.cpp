// HEADERS
// -----------------------------------------------------------------------------------
#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Vector utils
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

// Random utils
// -----------------------------------------------------------------------------------

int get_random(int limit) {
	return rand() % limit;
}

vector<int> get_random_vector(int length, int limit) {

	random_device random;
	mt19937 g(random());

	vector<int> random_vector = {};
	vector<int> sliced_vector = {};

	// Generate basic vector
	for (int i = -limit; i < limit - 1; i++) {
		random_vector.push_back(i);
	}

	// Shuffle randomly
	shuffle(random_vector.begin(), random_vector.end(), g);

	// Return first 'length' elements
	sliced_vector = { random_vector.begin(), random_vector.begin() + length};

	return sliced_vector;
}

bool is_zero_one_or_minus_one(int k) {
	return(k >= -1 && k <= 1);
}
