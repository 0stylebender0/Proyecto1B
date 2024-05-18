#pragma once
#include "Lista.h"
#include <stack>

double tiemposABB[4];

typedef struct NodoBB {
    char llave[120];		//Identificador del Nodo
	NodoBB* HijoIzquierdo;	//Puntero al Hijo Izquierdo
	NodoBB* HijoDerecho;	//Puntero al Hijo Derecho
}X;

bool insertarABB(NodoBB*& Raiz, const char* cualllave) {
    if (Raiz == NULL) {                         // Si el Arbol esta vacio
        Raiz = new NodoBB;                      // Reserva memoria para el nuevo Nodo
        strcpy_s(Raiz->llave, cualllave);       // Copia la llave al nuevo Nodo
        Raiz->HijoIzquierdo = NULL;             // Inicializa el puntero al Hijo Izquierdo
        Raiz->HijoDerecho = NULL;               // Inicializa el puntero al Hijo Derecho
        return true;
    }
    else {
        int comparacion = strcmp(cualllave, Raiz->llave);
        if (comparacion == 0) return false;                                             // Si la llave ya existe
        else if (comparacion < 0) return insertarABB(Raiz->HijoIzquierdo, cualllave);   // Si la llave es menor, busca en el Hijo Izquierdo
        else return insertarABB(Raiz->HijoDerecho, cualllave);                          // Si la llave es mayor, busca en el Hijo Derecho
    }
}

NodoBB* buscarABB(NodoBB* Raiz, const char* cualllave) {
    if (Raiz == NULL) {
        return NULL;                            //Si el Arbol esta vacio, retorna NULL
    }
    else {
        int comparacion = strncmp(cualllave, Raiz->llave, 9);
        if (comparacion == 0) return Raiz;                                          //Si la llave es igual al Nodo Raiz, retorna el Nodo Raiz
        else if (comparacion < 0) return buscarABB(Raiz->HijoIzquierdo, cualllave); //Si la llave es menor, busca en el Hijo Izquierdo
        else return buscarABB(Raiz->HijoDerecho, cualllave);                        //Si la llave es mayor, busca en el Hijo Derecho
    }
}

void destruirABB(NodoBB*& Raiz) {
    if (Raiz != NULL) {                         // Si el Arbol no esta vacio
        destruirABB(Raiz->HijoIzquierdo);       // Podar el Hijo Izquierdo
        destruirABB(Raiz->HijoDerecho);         // Podar el Hijo Derecho
        delete Raiz;                            // Libera la memoria del Nodo Raiz
        Raiz = NULL;                            // Elimina la direccion del Nodo Raiz
    }
}

void cargarABB(NodoBB*& PadronABB) {
    int cont = 1;
    time_t inicio, fin;
    inicio = time(NULL);
    FILE* archivo;

    cout << "\n\n----------------------------Cargando arbol--------------------------------" << endl;

    fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); //Abre el archivo del padron electoral con read.
    if (NULL == archivo) {
        printf("No se pudo abrir el archivo");
    }
    else {
        char agregado[119];								//Longitud de toda la cadena de un votante
        while (fgets(agregado, 119, archivo) != NULL) { //Evita que se desborde con basura al leer el fin de la cadena.
            if (cont % 2 != 0) {						//Esta condicion evita que se repitan los votantes ya que va de dos en dos.
                insertarABB(PadronABB, agregado);
            }
            cont++;
        }
        fclose(archivo); //cierra el archivo
    }

    fin = time(NULL);
    tiemposABB[0] = difftime(fin, inicio);
    printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
    cout << "----------------------------Arbol cargado--------------------------------\n\n" << endl;
    system("pause");
    system("CLS");
}

void resumenTiemposABB() {
    cout << "----------------------------Resumen de tiempos--------------------------------" << endl;
    cout << "Carga de padron: " << tiemposABB[0] << " segundos." << endl;
    cout << "Listado de votantes: " << tiemposABB[1] << " segundos." << endl;
    cout << "Ulitma busqueda de votante: " << tiemposABB[2] << " segundos." << endl;
    cout << "Liberacion de padron: " << tiemposABB[3] << " segundos." << endl;
    cout << "----------------------------Fin de resumen--------------------------------\n\n" << endl;
    system("pause");
    system("CLS");
}

void listarABB(NodoBB* Raiz) {
    if (Raiz != NULL) {
        listarABB(Raiz->HijoDerecho);
        printf("%s\n", Raiz->llave);
        listarABB(Raiz->HijoIzquierdo);
    }
}