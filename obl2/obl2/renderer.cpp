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
	Image* result = render_manager.ray_tracing(ImageIs::FullResult);
	cout << "3. Imagen generada correctamente" << endl << endl;

	// 4. Save result image
	if (!story_manager.save_result(result, ImageIs::FullResult)) {
		cerr << "Error: La imagen resultante no pudo ser guardada" << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "4. Imagen guardada correctamente" << endl;
	cout << "5. Generando imagenes auxiliares" << endl;
	result = render_manager.ray_tracing(ImageIs::Ambient); story_manager.save_result(result, ImageIs::Ambient);
	result = render_manager.ray_tracing(ImageIs::Diffuse); story_manager.save_result(result, ImageIs::Diffuse);
	result = render_manager.ray_tracing(ImageIs::Specular); story_manager.save_result(result, ImageIs::Specular);
	result = render_manager.ray_tracing(ImageIs::Reflection); story_manager.save_result(result, ImageIs::Reflection);
	result = render_manager.ray_tracing(ImageIs::Transmission); story_manager.save_result(result, ImageIs::Transmission);

	result = render_manager.ray_tracing(ImageIs::ColorAmbient); story_manager.save_result(result, ImageIs::ColorAmbient);
	result = render_manager.ray_tracing(ImageIs::ColorDiffuse); story_manager.save_result(result, ImageIs::ColorDiffuse);
	result = render_manager.ray_tracing(ImageIs::ColorSpecular); story_manager.save_result(result, ImageIs::ColorSpecular);
	
	post_render();
	cin.get();
	return 0;
}
