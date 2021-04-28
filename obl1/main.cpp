#include "obl1/headers.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	int opt = -1;
	int success;

	do {
		success = 0;

		system("CLS");
		cout << "Seleccionar programa:" << endl;
		cout << "  1 -> Juego (ultima version)" << endl;
		cout << "  0 -> Salir" << endl << endl;

		cin >> opt;
		cout << endl;

		switch (opt) {
			case(0): {
				cout << "Adios!" << endl;
				break;
			}
			case(1): {
				cout << "Ejecutando juego" << endl << endl;
				success = game();
				break;
			}
			default: {
				cout << "Comando erroneo, intentelo nuevamente" << endl;
			}
		}
		if (success != 0) {
			cout << "Ha ocurrido un error." << endl << endl;
			system("pause");
		}
		cout << endl;
	} while (opt != 0);

	return 0;
}
