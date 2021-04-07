#include "OpenGL-basico/exercises.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {
	
	int opt = -1;
	int success;

	do {
		success = 0;

		system("CLS");
		cout << "Seleccionar programa:" << endl;
		cout << "  1 -> Practico 1: Ejercicio 1" << endl;
		cout << "  2 -> Practico 1: Ejercicio 2" << endl;
		cout << "  3 -> Practico 1: Ejercicio 3" << endl;
		cout << "  4 -> Practico 1: Ejercicio 4" << endl;
		cout << "  5 -> Practico 2: Ejercicio 1" << endl;
		cout << "  6 -> Practico 2: Ejercicio 2" << endl;
		cout << "  7 -> Practico 2: Ejercicio 3" << endl;
		cout << "  8 -> Practico 2: Ejercicio 4" << endl;
		cout << "  9 -> Practico 3: Ejercicio 1" << endl;
		cout << " 10 -> Practico 3: Ejercicio 2" << endl;
		cout << " 11 -> Practico 3: Ejercicio 3" << endl;
		cout << " -1 -> Ejemplo Basico" << endl;
		cout << "  0 -> Salir" << endl << endl;

		cin >> opt;
		cout << endl;

		switch (opt) {
			case(-1): {
				cout << "Ejecutando Ejercicio base:" << endl;
				success = opengl_basico();
				break;
			}
			case(0): {
				cout << "Adios!" << endl;
				break;
			}
			case(1): {
				cout << "Ejecutando Practico 1: Ejercicio 1:" << endl << endl;
				success = pr1_ej1();
				break;
			}
			case(2): {
				cout << "Ejecutando Practico 1: Ejercicio 2:" << endl << endl;
				success = pr1_ej2();
				break;
			}
			case(3): {
				cout << "Ejecutando Practico 1: Ejercicio 3:" << endl << endl;
				success = pr1_ej3();
				break;
			}
			case(4): {
				cout << "Ejecutando Practico 1: Ejercicio 4:" << endl << endl;
				success = pr1_ej4();
				break;
			}
			case(5): {
				cout << "Ejecutando Practico 2: Ejercicio 1:" << endl << endl;
				success = pr2_ej1();
				break;
			}
			case(6): {
				cout << "Ejecutando Practico 2: Ejercicio 2:" << endl << endl;
				success = pr2_ej2();
				break;
			}
			case(7): {
				cout << "Ejecutando Practico 2: Ejercicio 3:" << endl << endl;
				success = pr2_ej3();
				break;
			}
			case(8): {
				cout << "Ejecutando Practico 2: Ejercicio 4:" << endl << endl;
				success = pr2_ej4();
				break;
			}
			case(9): {
				cout << "Ejecutando Practico 3: Ejercicio 1:" << endl << endl;
				success = pr3_ej1();
				break;
			}
			case(10): {
				cout << "Ejecutando Practico 3: Ejercicio 2:" << endl << endl;
				success = pr3_ej2();
				break;
			}
			case(11): {
				cout << "Ejecutando Practico 3: Ejercicio 3:" << endl << endl;
				success = pr3_ej3();
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
