#pragma once
#include "ABB.h"
#include "AVL.h"
#include "BTREE.h"
#include "Lista.h"
//-----------------------------------Lista dinamica-----------------------------------//
void listaDinamica(PtrT_Votante &ListaMaestra) {
	int opcion;
	char cedula[10];
	do{
		cout << "Lista Dinamica" << endl;
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
				system("CLS");
				break;

			default:
				cout << "Opcion no valida" << endl;
				break;
		}
	} while (opcion != 5);
}
//-----------------------------------Arbol Binario de Busqueda-----------------------------------//
void arbolBB(NodoBB* arbol){
	int opcion;
	char cedula[10];
	do {
		NodoBB* buscado;

		cout << "Arbol Binario Busqueda" << endl;
		cout << "1. Listar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Destruir" << endl;
		cout << "4. Resumen de tiempos" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			time_t inicio1, fin1;
			inicio1 = time(NULL);

			listarABB(arbol);

			fin1 = time(NULL);
			tiemposABB[1] = difftime(fin1, inicio1);
			printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin1, inicio1));
			cout << "----------------------------Padron listado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");

			break;

		case 2:
			cout << "Ingrese la cedula del votante a buscar: ";
			cin >> cedula;

			cout << "-----------------------------Buscando votante-------------------------------" << endl;

			time_t inicio2, fin2;
			inicio2 = time(NULL);

			buscado = buscarABB(arbol, cedula);

			fin2 = time(NULL);
			tiemposABB[2] = difftime(fin2, inicio2);
			
			if (buscado != NULL) {
				cout << buscado->llave << endl;
				cout << "----------------------------Votante encontrado-------------------------------" << endl;
			}
			else {
				cout << "----------------------------Votante no encontrado----------------------------" << endl;
			}

			printf("\nLa busqueda del votante ha tardado : %f segundos.\n", difftime(fin2, inicio2));

			delete(buscado);

			system("pause");
			system("CLS");

			break;

		case 3:
			time_t inicio3, fin3;
			inicio3 = time(NULL);

			cout << "\n\n----------------------------Liberando padron--------------------------------" << endl;

			destruirABB(arbol);

			fin3 = time(NULL);
			tiemposABB[3] = difftime(fin3, inicio3);
			printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin3, inicio3));
			cout << "----------------------------Padron libreado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");

			break;

		case 4:
			resumenTiemposABB();
			break;

		case 5:
			opcion = 5;
			system("CLS");
			break;

		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	} while (opcion != 5);
}
//-----------------------------------Arbol AVL-----------------------------------//
void arbolAVL(NodoAVL* arbol) {
	int opcion;
	char cedula[10];
	do {
		NodoAVL* buscado;

		cout << "Arbol AVL" << endl;
		cout << "1. Listar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Destruir" << endl;
		cout << "4. Resumen de tiempos" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			time_t inicio1, fin1;
			inicio1 = time(NULL);

			listarAVL(arbol);

			fin1 = time(NULL);
			tiemposAVL[1] = difftime(fin1, inicio1);
			printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin1, inicio1));
			cout << "----------------------------Padron listado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");

			break;

		case 2:
			cout << "Ingrese la cedula del votante a buscar: ";
			cin >> cedula;

			cout << "-----------------------------Buscando votante-------------------------------" << endl;

			time_t inicio2, fin2;
			inicio2 = time(NULL);

			buscado = buscarAVL(arbol, cedula);

			fin2 = time(NULL);
			tiemposAVL[2] = difftime(fin2, inicio2);

			if (buscado != NULL) {
				cout << buscado->llave << endl;
				cout << "----------------------------Votante encontrado-------------------------------" << endl;
			}
			else {
				cout << "----------------------------Votante no encontrado----------------------------" << endl;
			}

			printf("\nLa busqueda del votante ha tardado : %f segundos.\n", difftime(fin2, inicio2));

			delete(buscado);

			system("pause");
			system("CLS");

			break;

		case 3:
			time_t inicio3, fin3;
			inicio3 = time(NULL);

			cout << "\n\n----------------------------Liberando padron--------------------------------" << endl;

			destruirAVL(arbol);

			fin3 = time(NULL);
			tiemposAVL[3] = difftime(fin3, inicio3);
			printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin3, inicio3));
			cout << "----------------------------Padron libreado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");
			break;

		case 4:
			resumenTiemposAVL();
			break;

		case 5:
			opcion = 5;
			system("CLS");
			break;

		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	} while (opcion != 5);
}
//-----------------------------------Arbol BTREE-----------------------------------//
void arbolBTREE(NodoBtree* arbol) {
	int opcion, opt;
	opt = 3;
	char cedula[10];
	do {
		cout << "Arbol BTREE" << endl;
		cout << "1. Listar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Destruir" << endl;
		cout << "4. Resumen de tiempos" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			time_t inicio1, fin1;
			inicio1 = time(NULL);

			desplegar(arbol);

			fin1 = time(NULL);
			tiemposBTREE[1] = difftime(fin1, inicio1);
			printf("\nEl listado del padron ha tardado : %f segundos.\n", difftime(fin1, inicio1));
			cout << "----------------------------Padron listado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");

			break;

		case 2:
			cout << "Ingrese la cedula del votante a buscar: ";
			cin >> cedula;

			cout << "-----------------------------Buscando votante-------------------------------" << endl;

			time_t inicio2, fin2;
			inicio2 = time(NULL);

			buscarBtree(cedula, &opt, arbol);

			fin2 = time(NULL);
			tiemposBTREE[2] = difftime(fin2, inicio2);

			printf("\nLa busqueda del votante ha tardado : %f segundos.\n", difftime(fin2, inicio2));

			system("pause");
			system("CLS");

			break;

		case 3:
			time_t inicio3, fin3;
			inicio3 = time(NULL);

			cout << "\n\n----------------------------Liberando padron--------------------------------" << endl;

			//destruirBTREE(arbol);
			arbol = NULL;

			fin3 = time(NULL);
			tiemposBTREE[3] = difftime(fin3, inicio3);
			printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin3, inicio3));
			cout << "----------------------------Padron libreado--------------------------------\n\n" << endl;
			system("pause");
			system("CLS");
			break;

		case 4:
			resumenTiemposBTREE();
			break;

		case 5:
			opcion = 5;
			system("CLS");
			break;

		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	} while (opcion != 5);
}
//-----------------------------------Menu-----------------------------------//
void menu() {
	int opcion;
	do{
		cout << "Menu" << endl;
		cout << "1. Lista Dinamica" << endl;
		cout << "2. Arbol Binario de Busqueda" << endl;
		cout << "3. Arbol AVL" << endl;
		cout << "4. Arbol BTREE" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opcion;

		PtrT_Votante ListaMaestra = NULL;
		NodoBB *VotantesABB = NULL;
		NodoAVL* VotantesAVL = NULL;
		NodoBtree* VotantesBtree = NULL;

		switch (opcion) {
			case 1:
				cargarLista(ListaMaestra);
				listaDinamica(ListaMaestra);
				break;

			case 2:
				cargarABB(VotantesABB);
				arbolBB(VotantesABB);
				break;

			case 3:
				cargarAVL(VotantesAVL);
				arbolAVL(VotantesAVL);
				break;

			case 4:
				cargarBTREE(VotantesBtree);
				arbolBTREE(VotantesBtree);
				break;

			case 5:
				opcion = 5;
				system("CLS");
				break;

			default:
				cout << "Opcion no valida" << endl;
				break;
		}
	} while (opcion != 5);
}