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
Image Render::ray_tracing() {
	Image * result = new Image();
	Ray ray;
	// Obtener coordenadas de centro de proyección y ventana de plano

	for (size_t i = 0; i < IMAGE_WIDTH; i++) { // Por cada linea de barrido en la imagen
		for (size_t j = 0; j < IMAGE_HEIGHT; j++) { // Por cada pixel en la linea de barrido
			// Determinar rayo por centro de proyeccion y pixel
			// ray.origin = 
			// ray.direction = 
			result->image[i][j] = trace_rr(ray, 1); // Determinar el color del pixel (reflective and refrative)
		}
	}
	
	return *result;
}

// Intersect ray with objects and compute the shadow in the closes intersection
// Depth is the current depth in the tree of rays
Color Render::trace_rr(Ray ray, int depth) {
	if (depth > MAX_DEPTH) {
		return BACKGROUND_COLOR;
	}
	// Determinar la interseccion mas cercana de rayo con un objeto
	// if(intersection)  {
		// Calcular la normal en la interseccion
		// return shadow_rr(obj_intersecado_mas_cercano, ray, intersection, norm, depth)
	//}
	return BACKGROUND_COLOR;
}

// Problemas del algoritmo (Whitted)
// - El algoritmo es susceptible a problemas de presicion numerica
// - Los rayos generados pueden intersectar los objetos de donde salen
// - Los rayos de luz L no se refractan en su trayectoria hacia la luz
// TODO: Review type on object, point, and norm
Color Render::shadow_rr(short object, Ray ray, Vector point, float norm, int depth) {
	// color = termino del ambiente (luz ambiente) TODO: Constante?
	// for (cada luz) {
		// shadow_ray = // rayo desde el punto a la luz
		// if(norm * light_direction > 0) { // producto entre normal y direccion de la luz es positivo
			// Calcular cuanta luz es bloqueada por superficies opacas y transparentes
			// Usarlo para escalar los terminos difusos y especulares antes de añadirlos al color
			// 
			// if (object is reflective) {
				// ray_r = rayo en la direccion de refleccion desde el punto (inverse direction of reflection)
				// color_r = trace_rr(ray_r, depth + 1)
				// color_r = escalar color_r por coeficiente especular
				// color += color_r
			// }
			// if (object is refractive) { // obj es transparente
				// if(no ocurre reflexion interna total) {
					// ray_t = rayo en la direccion de refraccion desde punto (inverse direction of reflaction)
					// color_t =  trace_rr(ray_t, depth + 1)
					// color_t = escalar color_t por el coeficiente de transmisión
					// color += color_t
				// }
			// }
		// }
		// return color // devover color del rayo
	// }
	return BACKGROUND_COLOR;
}
