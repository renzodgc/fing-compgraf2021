// HEADERS
// -----------------------------------------------------------------------------------

#include "rectangle.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Rectangle::Rectangle(
	unsigned int id, Vector position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	float length, float width, float height) // Rectangle properties

	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {

	// Rectangle constructor
	this->type = ObjectIs::Rectangle;
	this->length = length;
	this->width = width;
	this->height = height;

	// Rectangle aux calls
	this->get_centers();
	this->get_normals();
}

// Main methods
// -----------------------------------------------------------------------------------

// Reference: https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere
// Ray vector: P + tU (P base point, U unit direction)
// Sphere surface: (X - C)^2 - r^2 = 0 (C sphere center, r sphere radius, X points that intersect sphere surface)
// Quadratic equation to solve: (P + tU - C)^2 - r^2 = 0 <=> U^2 t^2 + 2t U(P-C) + (P-C)^2 - r^2 = 0
// 
// TODO: https://www.notion.so/Arreglar-errores-de-presici-n-num-rica-para-las-intersecciones-dcbe39b3f097429e9f69d1633c26f046
//		 Esto por errores de presicion puede detectar que la interseccion ocurre dentro del objeto, esto es un problema
//		 Para resolverlo hay que restarle epsilon "hacia afuera" del objeto.
float Rectangle::intersect(Ray ray) {

	// For each face
	for (size_t i = 0; i < this->faces; i++) {
		float intersection_normal_ray = this->normals[i].inner_product(ray.direction);
		if (intersection_normal_ray > 1e-6) {
			Vector intersection_center_ray = this->centers[i] - ray.origin;
			float distance = intersection_center_ray.inner_product(this->normals[i]) / intersection_normal_ray;
			if (distance >= 0) {
				return distance;
			}
		}
	}

	return -1.f;
}


Vector Rectangle::get_normal(Vector point) {

	// Check if point intersects with right face
	if (point.x == this->centers[0].x) {
		return this->normals[0];
	} 
	// Check if point intersects with left face
	else if (point.x == this->centers[1].x) {
		return this->normals[1];
	} 
	// Check if point intersects with top face
	else if (point.y == this->centers[2].y) {
		return this->normals[2];
	}
	// Check if point intersects with bottom face
	else if (point.y == this->centers[3].y) {
		return this->normals[3];
	}
	// Check if point intersects with back face
	else if (point.z == this->centers[4].z) {
		return this->normals[4];
	}
	// Check if point intersects with front face
	else if (point.z == this->centers[5].z) {
		return this->normals[5];
	}

}

// Aux methods
// -----------------------------------------------------------------------------------

void Rectangle::get_centers() {

	float x = this->position.x;
	float y = this->position.y;
	float z = this->position.z;

	// Right face
	this->centers[0] = Vector(x + (this->width / 2), y, z);
	// Left face
	this->centers[1] = Vector(x - (this->width / 2), y, z);
	// Top face
	this->centers[2] = Vector(x, y + (this->height / 2), z);
	// Bottom face
	this->centers[3] = Vector(x, y - (this->height / 2), z);
	// Back face
	this->centers[4] = Vector(x, y, z + (this->length / 2));
	// Front face
	this->centers[5] = Vector(x, y, z - (this->length / 2));

}

void Rectangle::get_normals() {

	Vector length, width, height;

	// Get right face's normal
	width = this->centers[0] + this->centers[4];
	height = this->centers[0] + this->centers[2];
	this->normals[0] = width.cross_product(height);

	// Get left face's normal
	width = this->centers[1] + this->centers[4];
	height = this->centers[1] + this->centers[2];
	this->normals[1] = width.cross_product(height);
	
	// Get top face's normal
	width = this->centers[2] + this->centers[4];
	length = this->centers[2] + this->centers[0];
	this->normals[2] = width.cross_product(length);

	// Get bottom face's normal
	width = this->centers[3] + this->centers[4];
	length = this->centers[3] + this->centers[0];
	this->normals[3] = width.cross_product(length);
	
	// Get back face's normal
	length = this->centers[4] + this->centers[0];
	height = this->centers[4] + this->centers[2];
	this->normals[4] = height.cross_product(length);
	
	// Get front face's normal
	length = this->centers[5] + this->centers[0];
	height = this->centers[5] + this->centers[2];
	this->normals[5] = height.cross_product(length);

	// Normalize each of them
	for (size_t i = 0; i < this->faces; i++) {
		this->normals[i].normalize();
		this->normals[i].print();
		cout << endl;
	}
}