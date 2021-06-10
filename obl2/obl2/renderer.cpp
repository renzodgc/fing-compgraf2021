#include "headers.h"

using namespace std;

int main(int argc, char* argv[]) {

	Scene& scene_manager = Scene::get_instance();
	if (scene_manager.is_loaded()) {
		cout << "OK: El archivo config ha sido cargado correctamente" << endl;
		cin.get();
	}
	else {
		cerr << "Error: El archivo config no pudo ser cargado" << endl;
		cin.get();
	}

	return 0;
}
