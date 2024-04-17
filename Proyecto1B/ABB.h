#pragma once
#include "Lista.h"

typedef struct NodoBB {
	int llave;				//Identificador del Nodo
	NodoBB* HijoIzquierdo;	//Puntero al Hijo Izquierdo
	NodoBB* HijoDerecho;	//Puntero al Hijo Derecho
}X;

bool insertarABB(NodoBB*& Raiz, int cualllave){
	if (Raiz == NULL){				//Si el Arbol esta vacio
		Raiz = new(NodoBB);			//Reserva memoria para el nuevo Nodo
		Raiz->llave = cualllave;	//Asigna la llave al nuevo Nodo
		Raiz->HijoIzquierdo = NULL;	//Inicializa el puntero al Hijo Izquierdo
		Raiz->HijoDerecho = NULL;	//Inicializa el puntero al Hijo Derecho
		return true;
	}
	else{
		if (cualllave == Raiz->llave) return false;	//Si la llave ya existe 
		else
			if (cualllave < Raiz->llave) return insertarABB(Raiz->HijoIzquierdo, cualllave);	//Si la llave es menor, busca en el Hijo Izquierdo
			else return insertarABB(Raiz->HijoDerecho, cualllave);								//Si la llave es mayor, busca en el Hijo Derecho
	}
}

void destruirABB(NodoBB*& Raiz){
	if (Raiz != NULL){							//Si el Arbol no esta vacio
		destruirABB(Raiz->HijoIzquierdo);		//Podar el Hijo Izquierdo
		destruirABB(Raiz->HijoDerecho);			//Podar el Hijo Derecho
		printf("Borro : %i \n", Raiz->llave);	//Borra el Nodo Raiz
		delete(Raiz); Raiz = NULL;				//Libera la memoria del Nodo Raiz
	}
}

NodoBB* buscarABB(NodoBB* Raiz, int cualllave){
	if (Raiz == NULL){
		return NULL;	//Si el Arbol esta vacio, retorna NULL
	}
	else{
		if (cualllave == Raiz->llave) return Raiz;	//Si la llave es igual al Nodo Raiz, retorna el Nodo Raiz
		else
			if (cualllave < Raiz->llave) return buscarABB(Raiz->HijoIzquierdo, cualllave);	//Si la llave es menor, busca en el Hijo Izquierdo
			else return buscarABB(Raiz->HijoDerecho, cualllave);							//Si la llave es mayor, busca en el Hijo Derecho
	}
}