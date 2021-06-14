#include "headers.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	FreeImage_Initialise();

	Scene& scene_manager = Scene::get_instance();
	if (scene_manager.is_loaded()) {
		cout << "OK: El archivo config ha sido cargado correctamente" << endl;

		Story& story_manager = Story::get_instance();
		if (story_manager.is_created()) {
			cout << "OK: El directorio de historial ha sido creado correctamente" << endl;
			story_manager.run_ray_tracing();
		}
		else {
			cerr << "Error: El directorio de historial no pudo ser creado" << endl;
		}

		cin.get();
	}
	else {
		cerr << "Error: El archivo config no pudo ser cargado" << endl;
		cin.get();
	}

	FreeImage_DeInitialise();

	return 0;
}
