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
		cerr << "Error: El archivo config no pudo ser cargado" << endl << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "1. La escena ha sido cargado correctamente" << endl;

	// 2. Create story directory for saving intermediate and final images
	Story& story_manager = Story::get_instance();
	if (!story_manager.is_created()) {
		cerr << "Error: El directorio de historial no pudo ser creado" << endl << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "2. El directorio de historial ha sido creado correctamente" << endl;
			
	// 3. Initiate ray tracing
	Render& render_manager = Render::get_instance();	
	Image* result = render_manager.ray_tracing();
	cout << "3. Imagen generada correctamente" << endl;

	// 4. Save result image
	if (!story_manager.save_result(result)) {
		cerr << "Error: La imagen resultante no pudo ser guardada" << endl << endl;
		post_render();
		cin.get();
		return -1;
	}
	cout << "4. Imagen guardada correctamente" << endl;
			
	post_render();
	cin.get();
	return 0;
}
