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

// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
float Mesh::intersect(Ray ray) {
	float closest_distance = FOV + 1.f;

	// For each polygon in the mesh
	for (size_t i = 0; i < this->polygons.size(); i++) {

		Polygon* polygon = this->polygons[i];
		Vector normal = polygon->get_normal();

		// Check if normal and ray are parallel, if not, keep computing
		float parallelism = normal.inner_product(ray.direction);
		if (parallelism != 0) {
			float D = normal.inner_product(polygon->a);
			float distance = -(normal.inner_product(ray.origin) - D) / parallelism;

			// Check if distance is positive. If not, ray is coming from behind so no return
			if (distance > 0) {
				// Get point of intersection with plane
				Vector point = ray.origin + ray.direction.scalar_mult(distance);

				// Get polygon's edges
				Vector edge0 = polygon->b - polygon->a;
				Vector edge1 = polygon->c - polygon->b;
				Vector edge2 = polygon->a - polygon->c;
				
				// Get vectors from point to polygon's vertexes
				Vector C0 = point - polygon->a;
				Vector C1 = point - polygon->b;
				Vector C2 = point - polygon->c;
			
				// Way to check if point is inside triangle
				if (edge0.cross_product(C0).inner_product(normal) >= 0 &&
					edge1.cross_product(C1).inner_product(normal) >= 0 &&
					edge2.cross_product(C2).inner_product(normal) >= 0) {
					closest_distance = min(distance, closest_distance);
				}

			}

		}

	}

	if(closest_distance != FOV + 1.f)
		return closest_distance;

	return -1.f;
}

Vector Mesh::get_normal(Vector point, Ray ray) {
	
	for (size_t i = 0; i < this->polygons.size(); i++) {

		Polygon* polygon = this->polygons[i];
		Vector normal = polygon->get_normal(ray.direction);

		// Get polygon's edges
		Vector edge0 = polygon->b - polygon->a;
		Vector edge1 = polygon->c - polygon->b;
		Vector edge2 = polygon->a - polygon->c;

		// Get vectors from point to polygon's vertexes
		Vector C0 = point - polygon->a;
		Vector C1 = point - polygon->b;
		Vector C2 = point - polygon->c;

		// Way to check if point is inside triangle
		if (edge0.cross_product(C0).inner_product(normal) >= 0 &&
			edge1.cross_product(C1).inner_product(normal) >= 0 &&
			edge2.cross_product(C2).inner_product(normal) >= 0) {
			if (ray.direction.inner_product(normal) <= 0)
				return normal;
			else
				return -normal;
		}
	}

	return Vector(0, 0, 0);
}
