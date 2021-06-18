// HEADERS
// -----------------------------------------------------------------------------------

#include "cylinder.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Cylinder::Cylinder(
	unsigned int id, Vector* position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	float radius, float height) // Cylinder properties
	
	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {
		
	// Cylinder constructor
	this->type = ObjectIs::Cylinder;
	this->radius = radius;
	this->height = height;
}

// Main methods
// -----------------------------------------------------------------------------------

// Reference: https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere
// Solve quadratic equation
// TODO: https://www.notion.so/Arreglar-errores-de-presici-n-num-rica-para-las-intersecciones-dcbe39b3f097429e9f69d1633c26f046
//		 Esto por errores de presicion puede detectar que la interseccion ocurre dentro del objeto, esto es un problema
//		 Para resolverlo hay que restarle epsilon "hacia afuera" del objeto.
float Cylinder::intersect(Ray ray) {
	return -1.f;
}


Vector Cylinder::get_normal(Vector point) {
	Vector normal = point - *(this->position);
	normal.normalize();
	return(normal);
}
