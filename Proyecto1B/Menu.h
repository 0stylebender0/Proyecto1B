#pragma once
#include "ABB.h"
#include "AVL.h"
#include "BTREE.h"
#include "Lista.h"

void listaDinamica(PtrT_Votante &ListaMaestra) {
	int opcion;
	char cedula[10];
	do{
		cout << "\n\nLista Dinamica" << endl;
		cout << "1. Listar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Destruir" << endl;
		cout << "4. Resumen de tiempos" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;
		switch (opcion) {
			case 1:
				listar(ListaMaestra);
				break;
			case 2:
				cout << "Ingrese la cedula del votante a buscar: ";

				cin >> cedula;
				buscarLista(ListaMaestra, cedula);
				break;
			case 3:
				destuirLista(ListaMaestra);
				break;
			case 4:
				resumenTiemposLista();
				break;
			case 5:
				opcion = 5;
				break;
			default:
				cout << "Opcion no valida" << endl;
				break;
		}
	} while (opcion != 5);
}

void menu() {
	int opcion;
	do{
		cout << "\n\nMenu" << endl;
		cout << "1. Lista Dinamica" << endl;
		cout << "2. Arbol Binario de Busqueda" << endl;
		cout << "3. Arbol AVL" << endl;
		cout << "4. Arbol BTREE" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;

		PtrT_Votante ListaMaestra = NULL;

		switch (opcion) {
			case 1:
				cargarLista(ListaMaestra);
				listaDinamica(ListaMaestra);
				break;
			case 5:
				opcion = 5;
				break;
			default:
				cout << "Opcion no valida" << endl;
				break;
		}
	} while (opcion != 5);
}