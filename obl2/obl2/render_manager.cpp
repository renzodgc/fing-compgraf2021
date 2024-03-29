// HEADERS
// -----------------------------------------------------------------------------------
#include "render_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Render::Render() {}

Render& Render::get_instance() {
	static Render instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Main methods
// -----------------------------------------------------------------------------------

// http://www.fsz.bme.hu/~szirmay/ray.pdf
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted
// https://medium.com/nicos-softwaredev-projects/path-tracer-project-75d734e2789
// Light rays will be traced backwards (contrary to their natural direction), that is from the eye back to the lightsources.
Image* Render::ray_tracing(ImageIs type, bool anti_aliasing) {

	// 1. Get camera origin and window
	Camera* camera = Scene::get_instance().get_camera();
	Vector camera_eye = camera->get_position();
	Vector window_center = camera->get_window_position();

	// 2. Initiate aux objects
	Image * result = new Image();
	Ray * ray, *ray_00, * ray_01, * ray_10, * ray_11;
	Vector origin, direction;
	int object_lenght = Scene::get_instance().get_objects().size();
	// Obtener coordenadas de centro de proyecci�n y ventana de plano

	// 3. Main loop (pixel by pixel)
	for (int x = 0; x < IMAGE_WIDTH; x++) { // For each sweep line
		for (int y = 0; y < IMAGE_HEIGHT; y++) { // For each pixel

			// 3.1. Shoot ray from camera eye to window pixel
			ray = new Ray(
				camera_eye.copy(), // origin
				(Vector((float)(x - HALF_IMAGE_WIDTH), (float)(y - HALF_IMAGE_HEIGHT), window_center.z) - camera_eye.copy()) // direction (from eye to window's pixel)
			);

			// 3.2. Check if the image is an auxiliary for coefficients and run trace
			if(type == ImageIs::Ambient || type == ImageIs::Diffuse || type == ImageIs::Specular || type == ImageIs::Reflection || type == ImageIs::Transmission)
				result->image[x][y] = coef_trace_rr(ray, type);
			else {
				result->image[x][y] = trace_rr(ray, 1, type);
				if (ANTIALIASING) {
					ray_00 = new Ray( camera_eye.copy(), (Vector((float)(x - HALF_IMAGE_WIDTH) - ANTIALIASING_SHIFT, (float)(y - HALF_IMAGE_HEIGHT) - ANTIALIASING_SHIFT, window_center.z) - camera_eye.copy()));
					ray_01 = new Ray(camera_eye.copy(), (Vector((float)(x - HALF_IMAGE_WIDTH) - ANTIALIASING_SHIFT, (float)(y - HALF_IMAGE_HEIGHT) + ANTIALIASING_SHIFT, window_center.z) - camera_eye.copy()));
					ray_10 = new Ray(camera_eye.copy(), (Vector((float)(x - HALF_IMAGE_WIDTH) + ANTIALIASING_SHIFT, (float)(y - HALF_IMAGE_HEIGHT) - ANTIALIASING_SHIFT, window_center.z) - camera_eye.copy()));
					ray_11 = new Ray(camera_eye.copy(), (Vector((float)(x - HALF_IMAGE_WIDTH) + ANTIALIASING_SHIFT, (float)(y - HALF_IMAGE_HEIGHT) + ANTIALIASING_SHIFT, window_center.z) - camera_eye.copy()));
					result->image[x][y] = add_colors(result->image[x][y], add_colors(
						add_colors(trace_rr(ray_00, 1, type), trace_rr(ray_01, 1, type)),
						add_colors(trace_rr(ray_10, 1, type), trace_rr(ray_11, 1, type))
					));
					result->image[x][y] = scale_color(result->image[x][y], 1.f / 5.f);
					delete ray_00; delete ray_01; delete ray_10; delete ray_11;
				}
			}

			delete ray;
		}
	}

	return result;
}

// Intersect ray with objects and compute color based on refraction and reflection.
// Color can be shadowed by th closest intersection intersection
Color Render::trace_rr(Ray* ray, int depth, ImageIs type) {

	// 1. Return background color in case ray tree's depth is more than the max allowed
	if (depth > MAX_DEPTH) {
		return BACKGROUND_COLOR;
	}

	// Determine if an intersection occurs, if so get the closest object that intersects
	int intersection_index;
	float distance_intersection;
	tie(intersection_index, distance_intersection) = get_closest_intersected_object(ray);

	if (distance_intersection > FOV) {
		return BACKGROUND_COLOR;
	}
	if(intersection_index != -1)  {
		vector <Object*> objects = Scene::get_instance().get_objects();
		Vector intersection = ray->origin + (ray->direction * distance_intersection);
		Vector norm = objects[intersection_index]->get_normal(intersection, *ray);

		return shadow_rr(
			objects[intersection_index], // intersected object
			ray, // ray that intersects
			intersection, // point of intersection
			norm, // normal of intersection
			depth, // current depth
			type // image type
		);
	}
	return BACKGROUND_COLOR;
}

Color Render::coef_trace_rr(Ray* ray, ImageIs type) {
	// Determine if an intersection occurs, if so get the closest object that intersects
	int intersection_index;
	float distance_intersection;
	float coefficient = 0.f;
	tie(intersection_index, distance_intersection) = get_closest_intersected_object(ray);

	if (distance_intersection <= FOV && intersection_index != -1) {
		vector <Object*> objects = Scene::get_instance().get_objects();
		switch (type) {
		case ImageIs::Reflection:
			coefficient = objects[intersection_index]->is_reflective();
			break;
		case ImageIs::Transmission:
			coefficient = objects[intersection_index]->get_transmission_coef();
			break;
		case ImageIs::Ambient:
			coefficient = objects[intersection_index]->get_ambience_coef();
			break;
		case ImageIs::Diffuse:
			coefficient = objects[intersection_index]->get_diffuse_coef();
			break;
		case ImageIs::Specular:
			coefficient = objects[intersection_index]->get_specular_coef();
			break;
		}
		return scale_color(WHITE, coefficient);
	}
	return BLACK;
}

// Problemas del algoritmo (Whitted)
// - El algoritmo es susceptible a problemas de presicion numerica
// - Los rayos generados pueden intersectar los objetos de donde salen
// - Los rayos de luz L no se refractan en su trayectoria hacia la luz
Color Render::shadow_rr(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type) {
	Color color = get_ambient_component(object, type);
	color = add_colors(color, get_lights_component(object, ray, intersection_point, norm, type));
	color = add_colors(color, get_transmission_component(object, ray, intersection_point, norm, depth, type));
	color = add_colors(color, get_reflective_component(object, ray, intersection_point, norm, depth, type));
	return color;
}

// Aux methods - Intersection
// -----------------------------------------------------------------------------------

tuple<int, float> Render::get_closest_intersected_object(Ray* ray) {
	int intersection_index = -1;
	float distance_intersection = FOV + 1;
	float distance;
	vector <Object*> objects = Scene::get_instance().get_objects();
	for (size_t i = 0; i < objects.size(); i++) {
		distance = objects[i]->intersect(*ray);
		if (distance != -1.f && distance < distance_intersection) {
			distance_intersection = distance;
			intersection_index = i;
		}
	}
	return { intersection_index, distance_intersection };
}

tuple<vector<int>, vector<float>> Render::get_all_intersected_objects(Ray* ray) {
	vector<int> intersection_indexes;
	vector<float> intersected_distances;
	float distance;
	vector <Object*> objects = Scene::get_instance().get_objects();
	for (size_t i = 0; i < objects.size(); i++) {
		distance = objects[i]->intersect(*ray);
		if (distance != -1.f && distance <= FOV) {
			intersection_indexes.push_back((int)i);
			intersected_distances.push_back(distance);
		}
	}
	return { intersection_indexes, intersected_distances };
}

// Aux methods - Components
// -----------------------------------------------------------------------------------

Color Render::get_ambient_component(Object* object, ImageIs type) {
	// Apply Ambient Lightning (I_a * k_a * O_d)
	if (type == ImageIs::FullResult || type == ImageIs::ColorAmbient)
		return multiply_colors(scale_color(AMBIENT_LIGHTING, object->get_ambience_coef()), object->get_diffuse_color());
	else
		return BLACK;
}

Color Render::get_lights_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type) {
	vector <Object*> objects = Scene::get_instance().get_objects();
	Color light_component = BLACK;
	Color lights_component = BLACK;
	float transmission_coef_light, distance_from_light;
	int closest_intersection_index;
	float closest_intersection_distance;
	vector<int> intersection_indexes;
	vector<float> intersected_distances;
	int object_lenght = Scene::get_instance().get_objects().size();

	// Apply Shadow Lightning (Sum for every light)
	if (type == ImageIs::FullResult || type == ImageIs::ColorDiffuse || type == ImageIs::ColorSpecular) {
		vector <Light*> lights = Scene::get_instance().get_lights();
		for (size_t i = 0; i < lights.size(); i++) {
			light_component = BLACK;
			transmission_coef_light = 1.0f;

			// Cast a Ray from the intersection_point to the light source. This ray is a straight line.
			Ray* shadow_ray = new Ray(
				intersection_point.copy() + norm * EPSILON, // origin
				(lights[i]->get_position().copy() - (intersection_point.copy() + norm * EPSILON)) // direction (from eye to window's pixel)
			);
			// If no objects stands it applies directly

			// Ligting affects object if the inner product between its direction and the objects norm is positive.
			if (shadow_ray->direction.inner_product(norm) > 0) {
				distance_from_light = intersection_point.euclid_distance(lights[i]->get_position());

				// f_att * I_p * (Specular + Diffuse)
				light_component = scale_color(
					multiply_colors(
						add_colors(
							get_diffuse_component(object, ray, intersection_point, norm, type, shadow_ray),
							get_specular_component(object, ray, intersection_point, norm, type, shadow_ray)
						),
						lights[i]->get_color() // I_pi
					),
					min(LIGHT_ATTENUATION_C0_ADDITION + (LIGHT_ATTENUATION_C1_MULTIPLIER / distance_from_light), 1.f)
				);

				// Check if an object stands between the intersection point and the light source.
				tie(intersection_indexes, intersected_distances) = get_all_intersected_objects(shadow_ray);

				if (!intersection_indexes.empty()) {
					// At least one object is in the same direction as the light. Shadow may be cast
					for (size_t i = 0; i < intersection_indexes.size(); i++) {
						if (intersected_distances[i] < distance_from_light) {
							// Object stands between the surface and the source of light.
							// Substract from the transmission coefficient accounting for the light it obscures
							// Convert transmission coefficient [0,1] (opaque, translucid) to [1,0] (translucid, opaque) by using f(x) = 1 - x
							transmission_coef_light -= (1 - objects[intersection_indexes[i]]->get_transmission_coef());
						} // Else light stands in between, object is not factored
					}
					transmission_coef_light = min(1.f, max(0.f, transmission_coef_light));
					
					tie(closest_intersection_index, closest_intersection_distance) = get_closest_intersected_object(shadow_ray);
					if (closest_intersection_distance < distance_from_light) {
						// S_i * (Transmitted Color) * f_att * I_p * (Specular + Diffuse)
						light_component = scale_color(
							multiply_colors( // 
								light_component,
								scale_color( // Project the object's color into the shadow
									objects[closest_intersection_index]->get_diffuse_color(),
									objects[closest_intersection_index]->get_diffuse_coef()
								)
							),
							transmission_coef_light // S_i
						);
					}
				}
				// Else: No object stands between the surface and the light. And the light fully reachs the object (transmission_coef_light = 1.0f)
				lights_component = add_colors(lights_component, light_component);
			}
			delete shadow_ray;
		}
	}
	return lights_component;
}

Color Render::get_diffuse_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type, Ray* shadow_ray) {
	Color diffuse_component = BLACK;
	// Diffuse Component = k_d * O_d * (N * L_i)
	if (type == ImageIs::FullResult || type == ImageIs::ColorDiffuse) {
		diffuse_component = scale_color(
			scale_color(
				object->get_diffuse_color(), // O_d
				object->get_diffuse_coef() // k_d
			),
			max(0.f, shadow_ray->direction.inner_product(norm)) // L_i * N
		);
	}
	return diffuse_component;
}

Color Render::get_specular_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type, Ray* shadow_ray) {
	Color specular_component = BLACK;
	// Specular Component = k_s * O_s * (R * V)^n
	if (type == ImageIs::FullResult || type == ImageIs::ColorSpecular) {
		
		Vector R_vector = norm.scalar_mult(2).scalar_mult( // 2N *
			norm.inner_product(shadow_ray->direction) // ( N . L )
		) - shadow_ray->direction; // - L

		Vector V_vector = -ray->direction; // V

		specular_component = scale_color(
			scale_color(
				object->get_specular_color(), // O_s
				object->get_specular_coef() // k_s
			),
			pow(R_vector.inner_product(V_vector), SPECULAR_EXPONENT) // ( R . V )^n
		);
		
	}
	return specular_component;
}

// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/adding-reflection-and-refraction
// http://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf
// https://github.com/TomCrypto/Lambda
Color Render::get_transmission_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type) {
	Color refractive_color = BLACK;
	if (type == ImageIs::FullResult && !object->is_opaque()) {
		float cosi = min(1.f, max(-1.f, ray->direction.inner_product(norm))); // Cosine of the intersection before refraction
		vector <Object*> objects = Scene::get_instance().get_objects();
		float etai = VACUUM; // Medium before refraction
		float etat = VACUUM; // Medium after refraction

		// Determine if entering or leaving surface
		if (cosi <= 0) {
			// Incident and normal have opposite directions, so the ray is outside the material.
			cosi = -cosi; // Ray is outside the surface, invert it so cos(thetha) is positive
			if (ray->refraction_stack.empty()) {
				etai = VACUUM;
			} else {
				etai = objects[ray->refraction_stack.top()]->get_refraction_coef();
			}
			etat = object->get_refraction_coef();
			ray->refraction_stack.push(object->get_id());
		}
		else {
			// Incident and normal have the same direction, ray is inside the material.
			norm = -norm; // Ray is inside the surface, cos(thetha) is already positive. But norm's direction needs to be reversed
			etai = object->get_refraction_coef();
			if (ray->refraction_stack.empty()) {
				etat = VACUUM;
			} else {
				ray->refraction_stack.pop();
				if (ray->refraction_stack.empty()) {
					etat = VACUUM;
				}
				else {
					etat = objects[ray->refraction_stack.top()]->get_refraction_coef();
				}
				
			}
		}
		// Get cosine of reflection angle
		float eta = etai / etat;
		float cost = 1.f - pow(eta, 2.f) * (1.f - pow(cosi, 2.f));
		if (cost >= 0.f) {
			// Refraction occurs
			ray->origin = intersection_point - (norm * EPSILON);
			Vector refraction_direction = (ray->direction * eta) + (norm * (eta * cosi - sqrtf(cost)));
			refraction_direction.normalize();
			ray->direction = refraction_direction;

			refractive_color = trace_rr(ray, depth + 1, type);
			// Transmission/Refraction component (k_t * I_t)
			refractive_color = scale_color(refractive_color, object->get_transmission_coef());
		}
		// If k < 0. Total internal reflection occurs
	}
	return refractive_color;
}

// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/adding-reflection-and-refraction
// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
Color Render::get_reflective_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type) {
	Color reflective_color = BLACK;
	// Reflective component (k_t * I_t)
	if (type == ImageIs::FullResult && object->is_reflective()) {
		ray->origin = intersection_point + (norm * EPSILON);
		// Reflect the ray's direction symetrically in regards to the norm.
		ray->direction = ray->direction - (norm * (2 * (ray->direction.inner_product(norm)))); // I - 2N(N . I)

		reflective_color = trace_rr(ray, depth + 1, type);
		reflective_color = scale_color(reflective_color, object->get_specular_coef());
	}
	return reflective_color;
}
