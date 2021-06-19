// HEADERS
// -----------------------------------------------------------------------------------

#include "mesh.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// MESH METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Mesh::Mesh(
	unsigned int id, Vector position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	vector<Polygon*> polygons) // Mesh properties

	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {

	// Rectangle constructor
	this->type = ObjectIs::TriangleMesh;
	this->polygons = polygons;

}

// Main methods
// -----------------------------------------------------------------------------------

float Mesh::intersect(Ray ray) {
	return -1.f;
}

Vector Mesh::get_normal(Vector point) {
	return this->polygons[0]->get_normal();
}
