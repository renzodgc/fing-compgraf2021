#include "headers.h"

using namespace std;

void pre_render() {
	FreeImage_Initialise();
}

void post_render() {
	FreeImage_DeInitialise();
}

int main(int argc, char* argv[]) {
	
	// 0. Pre-render: Initialise freeimage
	pre_render();

	// 1. Load scene from config file
	Scene& scene_manager = Scene::get_instance();
	if (!scene_manager.is_loaded()) {
		cerr << "Error: La escena no pudo ser cargada" << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "1. La escena ha sido cargada correctamente" << endl;

	// 2. Create story directory for saving intermediate and final images
	Story& story_manager = Story::get_instance();
	if (!story_manager.is_created()) {
		cerr << "Error: El directorio de historial no pudo ser creado" << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "2. El directorio de historial ha sido creado correctamente" << endl;
			
	// 3. Initiate ray tracing
	Render& render_manager = Render::get_instance();	
	Image* result = render_manager.ray_tracing(ImageIs::FullResult, ANTIALIASING);
	cout << "3. Imagen generada correctamente" << endl;

	// 4. Save result image
	if (!story_manager.save_result(result, ImageIs::FullResult)) {
		cerr << "Error: La imagen resultante no pudo ser guardada" << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "4. Imagen guardada correctamente" << endl;


	// 5. Run ray tracing to generate intermediate results
	cout << "5. Generando resultados intermedios:" << endl;
	// Coefficient results
	result = render_manager.ray_tracing(ImageIs::Ambient, false); story_manager.save_result(result, ImageIs::Ambient);
	cout << "    5.1. Coeficiente ambiental" << endl;
	result = render_manager.ray_tracing(ImageIs::Diffuse, false); story_manager.save_result(result, ImageIs::Diffuse);
	cout << "    5.2. Coeficiente difuso" << endl;
	result = render_manager.ray_tracing(ImageIs::Specular, false); story_manager.save_result(result, ImageIs::Specular);
	cout << "    5.3. Coeficiente especular" << endl;
	result = render_manager.ray_tracing(ImageIs::Reflection, false); story_manager.save_result(result, ImageIs::Reflection);
	cout << "    5.4. Coeficiente de reflexion" << endl;
	result = render_manager.ray_tracing(ImageIs::Transmission, false); story_manager.save_result(result, ImageIs::Transmission);
	cout << "    5.5. Coeficiente de transmision" << endl;
	// Color results
	result = render_manager.ray_tracing(ImageIs::ColorAmbient, false); story_manager.save_result(result, ImageIs::ColorAmbient);
	cout << "    5.6. Color ambiental" << endl;
	result = render_manager.ray_tracing(ImageIs::ColorDiffuse, false); story_manager.save_result(result, ImageIs::ColorDiffuse);
	cout << "    5.7. Color difuso" << endl;
	result = render_manager.ray_tracing(ImageIs::ColorSpecular, false); story_manager.save_result(result, ImageIs::ColorSpecular);
	cout << "    5.8. Color especular" << endl;

	post_render();
	cin.get();
	return 0;
}
