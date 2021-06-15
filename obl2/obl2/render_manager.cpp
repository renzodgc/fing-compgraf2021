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

// http://www.fsz.bme.hu/~szirmay/ray.pdf
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted
// https://medium.com/nicos-softwaredev-projects/path-tracer-project-75d734e2789
// Light rays will be traced backwards (contrary to their natural direction), that is from the eye back to the lightsources.
Image* Render::ray_tracing() {
	cout << "Iniciando algoritmo de Ray Tracing" << endl;

	Camera * camera = Scene::get_instance().get_camera();
	//vector <Light*> lights = scene_manager.get_lights();
	//vector <Object*> objects = scene_manager.get_objects();

	Vector * camera_eye = camera->get_position();
	Vector * window_center = camera->get_window_position();
	Vector window_bottom_left = *window_center + Vector(-HALF_IMAGE_WIDTH, -HALF_IMAGE_HEIGHT, 0);
	Vector window_bottom_right = *window_center + Vector(HALF_IMAGE_WIDTH, -HALF_IMAGE_HEIGHT, 0);
	Vector window_top_left = *window_center + Vector(-HALF_IMAGE_WIDTH, HALF_IMAGE_HEIGHT, 0);
	Vector window_top_right = *window_center + Vector(HALF_IMAGE_WIDTH, HALF_IMAGE_HEIGHT, 0);

	Image * result = new Image();
	Ray ray;
	Vector origin, direction;
	// Obtener coordenadas de centro de proyección y ventana de plano

	for (int x = 0; x < IMAGE_WIDTH; x++) { // For each sweep line
		if (x % 64 == 0) {
			cout << "Ray Tracing (" << x / 64 << "/" << IMAGE_WIDTH / 64 << ")" << endl;
		}
		for (int y = 0; y < IMAGE_HEIGHT; y++) { // For each pixel
			// TODO: Revisar si ray tiene que ser punteros
			ray = Ray(
				Vector((float)(x - HALF_IMAGE_WIDTH), (float)(y - HALF_IMAGE_HEIGHT), window_center->z), // origin
				(Vector((float)(x - HALF_IMAGE_WIDTH), (float)(y - HALF_IMAGE_HEIGHT), window_center->z) - Vector(camera_eye->x, camera_eye->y, camera_eye->z)) // direction (from eye to window's pixel)
			);
			result->image[x][y] = trace_rr(ray, 1);
		}
	}

	cout << "Fin de algoritmo de Ray Tracing" << endl << endl;
	return result;
}

// Intersect ray with objects and compute colour based on refraction and reflection.
// Color can be shadowed by th closest intersection intersection
// Depth is the current depth in the tree of rays
Color Render::trace_rr(Ray ray, int depth) {
	if (depth > MAX_DEPTH) {
		return BACKGROUND_COLOR;
	}
	// Determine if an intersection occurs, if so get the closest object that intersects
	size_t intersection_index;
	float distance_intersection;
	tie(intersection_index, distance_intersection) = get_closest_intersected_object(ray);
	if (distance_intersection > FOV) {
		return BACKGROUND_COLOR;
	}
	if(intersection_index != -1)  {
		Vector intersection = ray.origin + (ray.direction * distance_intersection); // TODO: Revisar?
		
		vector <Object*> objects = Scene::get_instance().get_objects();
		return shadow_rr(
			objects[intersection_index], // intersected object
			ray, // ray that intersects
			intersection, // point of intersection
			objects[intersection_index]->get_normal(intersection), // normal of intersection
			depth // current depth
		);
	}
	return BACKGROUND_COLOR;
}

// Problemas del algoritmo (Whitted)
// - El algoritmo es susceptible a problemas de presicion numerica
// - Los rayos generados pueden intersectar los objetos de donde salen
// - Los rayos de luz L no se refractan en su trayectoria hacia la luz
// TODO: Review type on object, point, and norm
Color Render::shadow_rr(Object* object, Ray ray, Vector intersection_point, Vector norm, int depth) {
	Color color = multiply_colors(scale_color(AMBIENT_LIGHTING, object->get_ambience_coef()), object->get_diffuse_color());
	Color diffuse_component = BLACK;
	Color specular_component = BLACK;
	Color refractive_color = BLACK;
	Color reflective_color = BLACK;
	vector <Light*> lights = Scene::get_instance().get_lights();
	size_t intersection_index;
	float distance_intersection, distance_from_light;
	for (size_t i = 0; i < lights.size(); i++) {

		// Get light's direction (Ray between intersection and light source)
		Ray shadow_ray = Ray(
			intersection_point.copy(), // origin
			(intersection_point.copy() - *(lights[i]->get_position())) // direction (from eye to window's pixel)
		); // TODO: Point - light or light - point?

		// Ligting affects object if the inner product between its direction and the objects norm is positive.
		if(shadow_ray.direction.inner_product(norm) > 0) {
			vector <Object*> objects = Scene::get_instance().get_objects();
			tie(intersection_index, distance_intersection) = get_closest_intersected_object(ray);
			distance_from_light = intersection_point.euclid_distance(*(lights[i]->get_position()));
			if ((intersection_index != -1) && (distance_intersection <= FOV) && (distance_intersection < distance_from_light)) {
				// An object stands between the surface and the source of light
				if (!objects[intersection_index]->is_opaque()) {
					// TODO: For shadow color: Cuando mandas el rayo hacia la luz para calcular la sombra de algo (estos rayos) no se pueden desviar! Las sombras son lineas

					// TODO: Refractions

					// Get Refraction Angle (Snell Law)
					
					// if(no ocurre reflexion interna total) {
						/*Ray refractive_ray = Ray(
							intersection_point.copy(), // origin

						);*/ // Inverse direction as refraction refraccion desde punto(inverse direction of reflaction)
						// color_t =  trace_rr(ray_t, depth + 1)
						// color_t = escalar color_t por el coeficiente de transmision TODO: Del objeto que viene la luz?
						// color += color_t
					// }
				}
				if (objects[intersection_index]->is_reflective()) {
					// TODO: Verificar que la direccion de reflexion sea la simetrica al rayo anterior respecto a la normal
					Ray reflective_ray = Ray(
						intersection_point.copy(), // origin
						norm * ((ray.direction * -1.f) * norm) * 2 + ray.direction // 2(V * n) * n - V; V = -ray
					); // rayo en la direccion de refleccion desde el punto (inverse direction of reflection)

					reflective_color = trace_rr(reflective_ray, depth + 1);
					reflective_color = scale_color(reflective_color, object->get_specular_coef());
					// TODO: Multiplicar por el inverso de la distancia? I_r\lambda I_t\lambda (PPT Kajiya)
				}

				// Calcular cuanta luz es bloqueada por superficies opacas y transparentes
				// Usarlo para escalar los terminos difusos y especulares antes de añadirlos al color
				color = add_colors(
					color,
					add_colors(refractive_color, reflective_color)
				);
				/*color = add_colors(
					color,
					add_colors(
						scale_color(refractive_color, object.get_diffuse_color()),
						scale_color(reflective_color, object.get_specular_color())
					)
				);*/
			} else /*if(distance_from_light <= FOV)*/ {
				// No object stands between the surface and the light. And the light reachs the object
				// TODO: Revisar
				Vector blinn = ((shadow_ray.direction + (ray.direction * -1.f)) / 2);
				blinn.normalize();
				diffuse_component = scale_color(
					multiply_colors(lights[i]->get_color(), object->get_diffuse_color()),
					max(0.f, shadow_ray.direction.inner_product(norm))
				);
				specular_component = scale_color(
					multiply_colors(lights[i]->get_color(), object->get_specular_color()),
					max(0.f, blinn.inner_product(norm)) // pow(max(0, blinn * norm), mat->GetShine()
				);
				// TODO: Multiplicar por el inverso de la distancia?

				color = add_colors(
					color,
					add_colors(
						multiply_colors(scale_color(diffuse_component, object->get_diffuse_coef()), object->get_diffuse_color()),
						multiply_colors(scale_color(specular_component, object->get_specular_coef()), object->get_specular_color())
					)
				);
			} //else { TODO: Light is outside FOV }
		}
	}
	return color;
}


tuple<size_t, float> Render::get_closest_intersected_object(Ray ray) {
	size_t intersection_index = -1;
	float distance_intersection = FOV + 1;
	float distance;
	vector <Object*> objects = Scene::get_instance().get_objects();
	for (size_t i = 0; i < objects.size(); i++) {
		distance = objects[i]->intersect(ray);
		if (distance < distance_intersection) {
			distance_intersection = distance;
			intersection_index = i;
		}
	}
	return { intersection_index, distance_intersection };
}
