#pragma once
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

using namespace std;
double tiemposLista[4];

typedef struct T_Votante { //Se define la estructura para los votantes
	char cedula[10];
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_Votante* PtrSiguiente;
}*PtrT_Votante;

void agregarVotante(PtrT_Votante& ListaMaestra, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante);

	Aux->PtrSiguiente = ListaMaestra;
	ListaMaestra = Aux;

	//Cedula
	for (int ce = 0; ce < 9; ce++) { 
		ListaMaestra->cedula[ce] = agregado[ce];
	}
	ListaMaestra->cedula[9] = '\0';

	//Codigo electoral
	for (int co = 10; co < 16; co++) { 
		ListaMaestra->codelec[co - 10] = agregado[co];
	}
	ListaMaestra->codelec[6] = '\0';

	//Sexo
	ListaMaestra->sexo = agregado[17];

	//Fecha
	for (int fe = 19; fe < 27; fe++) {
		ListaMaestra->fecha[fe - 19] = agregado[fe];
	}
	ListaMaestra->fecha[8] = '\0';

	//Numero de junta
	for (int nu = 28; nu < 33; nu++) {
		ListaMaestra->numjun[nu - 28] = agregado[nu];
	}
	ListaMaestra->numjun[5] = '\0';

	//Nombre
	for (int nom = 34; nom < 64; nom++) {
		ListaMaestra->nombre[nom - 34] = agregado[nom];
	}
	ListaMaestra->nombre[30] = '\0';

	//Primer apellido
	for (int pa = 65; pa < 91; pa++) {
		ListaMaestra->papellido[pa - 65] = agregado[pa];
	}
	ListaMaestra->papellido[26] = '\0';

	//Segundo apellido
	for (int sa = 92; sa < 118; sa++) { 
		ListaMaestra->sapellido[sa - 92] = agregado[sa];
	}
	ListaMaestra->sapellido[26] = '\0';
}

void cargarLista(PtrT_Votante& ListaMaestra) {
	int cont = 1;
	time_t inicio, fin;		
	inicio = time(NULL);	
	FILE* archivo;

	cout << "\n\n----------------------------Cargando lista--------------------------------" << endl;

	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); //Abre el archivo del padron electoral con read.
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		char agregado[119];								//Longitud de toda la cadena de un votante
		while (fgets(agregado, 119, archivo) != NULL) { //Evita que se desborde con basura al leer el fin de la cadena.
			if (cont % 2 != 0) {						//Esta condicion evita que se repitan los votantes ya que va de dos en dos.
				agregarVotante(ListaMaestra, agregado);
			}
			cont++;
		}
		fclose(archivo); //cierra el archivo
	}

	fin = time(NULL);
	tiemposLista[0] = difftime(fin, inicio);
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Lista cargada----------------------------------------\n\n" << endl;
	system("pause");
	system("CLS");
}

void listar(PtrT_Votante& ListaMaestra) {
	PtrT_Votante Aux = ListaMaestra;
	time_t inicio, fin;
	inicio = time(NULL);
	cout << "\n\n----------------------------Listando votantes--------------------------------" << endl;

	if (Aux != NULL) {
		while (Aux != NULL) {
			cout << Aux->cedula << " " << Aux->codelec << " " << Aux->sexo << " " << Aux->fecha << " " << Aux->numjun << " " << Aux->nombre << " " << Aux->papellido << " " << Aux->sapellido << endl;
			Aux = Aux->PtrSiguiente;
		}
	}
	fin = time(NULL);
	tiemposLista[1] = difftime(fin, inicio);
	printf("\nLa lista de votantes ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Votantes listados-----------------------------------\n\n" << endl;
	system("pause");
	system("CLS");
}

void buscarLista(PtrT_Votante& Lista, char cual[9]) {
	time_t inicio, fin;
	inicio = time(NULL);

	cout << "\n\n----------------------------Buscando votante--------------------------------" << endl;

	bool encontro = false;
	PtrT_Votante Aux;
	Aux = Lista;

	while ((!encontro == true) && (Aux != NULL)) {
		if (strncmp(Aux->cedula, cual, 9) == 0) {
			encontro = true;
			cout << Aux->cedula << " " << Aux->codelec << " " << Aux->sexo << " " << Aux->fecha << " " << Aux->numjun << " " << Aux->nombre << " " << Aux->papellido << " " << Aux->sapellido << endl;
		}
		else {
			Aux = Aux->PtrSiguiente;
		}
	}

	fin = time(NULL);
	tiemposLista[2] = difftime(fin, inicio);

	if (encontro == false) {
		cout << "----------------------------Votante no encontrado--------------------------------\n\n" << endl;
		printf("\nLa busqueda del votante ha tardado : %f segundos.\n", difftime(fin, inicio));
		system("pause");
		system("CLS");
	}
	else {
		cout << "----------------------------Votante encontrado-----------------------------------\n\n" << endl;
		printf("\nLa busqueda del votante ha tardado : %f segundos.\n", difftime(fin, inicio));
		system("pause");
		system("CLS");
	}
}

void destuirLista(PtrT_Votante& ListaV) {
	PtrT_Votante Aux = ListaV;
	time_t inicio, fin;
	inicio = time(NULL);

	cout << "\n\n----------------------------Liberando padron--------------------------------" << endl;

	while (Aux != NULL) {
		ListaV = ListaV->PtrSiguiente;  //ListaV apunta al siguiente nodo antes de eliminar al actual.
		delete(Aux);					//Elimina el nodo donde este apuntando Aux
		Aux = ListaV;					//Aux apunta a donde apuntaba listaV.
	}

	fin = time(NULL);
	tiemposLista[3] = difftime(fin, inicio);
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron liberado--------------------------------\n\n" << endl;
	system("pause");
	system("CLS");
}

void resumenTiemposLista() {
	cout << "----------------------------Resumen de tiempos----------------------------" << endl;
	cout << "Carga de padron: " << tiemposLista[0] << " segundos." << endl;            
	cout << "Listado de votantes: " << tiemposLista[1] << " segundos." << endl;        
	cout << "Ulitma busqueda de votante: " << tiemposLista[2] << " segundos." << endl; 
	cout << "Liberacion de padron: " << tiemposLista[3] << " segundos." << endl;	   
	cout << "----------------------------Fin de resumen--------------------------------\n\n" << endl;
}