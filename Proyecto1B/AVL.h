#pragma once
#include "Lista.h"

struct Nodo {
	int llave;
	struct Nodo* izq;
	struct Nodo* derecha;
	int altura;
};