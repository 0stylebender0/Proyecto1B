#pragma once
#include "Lista.h"

double tiemposBTREE[4];

#define MAX 4
#define MIN 2

struct NodoBtree {
	char llave[MAX + 1][119];
	int count;
	NodoBtree* link[MAX + 1];
};

NodoBtree* root;

//Crear nodo 
NodoBtree* crearnodo(const char llave[119], NodoBtree* hijo) {
    NodoBtree* NuevoNodo = new NodoBtree;
    strncpy_s(NuevoNodo->llave[0], sizeof(NuevoNodo->llave[0]), llave, _TRUNCATE);
    NuevoNodo->count = 1;
    NuevoNodo->link[0] = NULL;
    NuevoNodo->link[1] = hijo;
    return NuevoNodo;
}

//coloca el nodo en la posicion adecuada, de acuerdo a su valor
void Colocarnodo(const char* val, int pos, NodoBtree* node, NodoBtree* hijo) {
	int j = node->count;
	while (j > pos) {
		strncpy_s(node->llave[j + 1], sizeof(node->llave[j]), node->llave[j], _TRUNCATE);
		node->link[j + 1] = node->link[j];
		j--;
	}
	strncpy_s(node->llave[j + 1], sizeof(node->llave[j]), val, _TRUNCATE);
	node->link[j + 1] = hijo;
	node->count++;
}

void PartirNodo(const char* val, char* pval, int pos, NodoBtree* node, NodoBtree* hijo, NodoBtree** NuevoNodo) {
	int median, j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*NuevoNodo = new NodoBtree;
	j = median + 1;
	while (j <= MAX) {
		strncpy_s((*NuevoNodo)->llave[j - median], sizeof((*NuevoNodo)->llave[j]), node->llave[j], _TRUNCATE);
		(*NuevoNodo)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*NuevoNodo)->count = MAX - median;

	if (pos <= MIN) {
		Colocarnodo(val, pos, node, hijo);
	}
	else {
		Colocarnodo(val, pos - median, *NuevoNodo, hijo);
	}
	strncpy_s(pval, sizeof(node->llave[node->count]), node->llave[node->count], _TRUNCATE);
	(*NuevoNodo)->link[0] = node->link[node->count];
	node->count--;
}

//colocar valor
int SetValorNodo(const char* val, char* pval, NodoBtree* node, NodoBtree** hijo) {

	int pos;
	if (!node) {
		strcpy_s(pval, 119, val);
		*hijo = NULL;
		return 1;
	}

	if (strncmp(val, node->llave[1], 9) < 0) {
		pos = 0;
	}
	else {
		for (pos = node->count;
			(strncmp(val, node->llave[pos], 9) < 0 && pos > 1); pos--);
		if (strncmp(val, node->llave[pos], 9) == 0) {
			return 0;
		}
	}
	if (SetValorNodo(val, pval, node->link[pos], hijo)) {
		if (node->count < MAX) {
			Colocarnodo(pval, pos, node, *hijo);
		}
		else {
			PartirNodo(pval, pval, pos, node, *hijo, hijo);
			return 1;
		}
	}
	return 0;
}

//inserta valores en el btree
void insertar(const char* val, NodoBtree*& PadronBtree) {
	char i[119];
	NodoBtree* hijo;
	char flag = SetValorNodo(val, i, PadronBtree, &hijo);

	if (flag)
		PadronBtree = crearnodo(i, hijo);
}

void cargarBTREE(NodoBtree* &PadronBtree) {
	int cont = 1;
	time_t inicio, fin;
	inicio = time(NULL);
	FILE* archivo;

	cout << "\n\n----------------------------Cargando BTREE--------------------------------" << endl;

	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); //Abre el archivo del padron electoral con read.
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		char agregado[119];								//Longitud de toda la cadena de un votante
		while (fgets(agregado, 119, archivo) != NULL) { //Evita que se desborde con basura al leer el fin de la cadena.
			if (cont % 2 != 0) {						//Esta condicion evita que se repitan los votantes ya que va de dos en dos.
				insertar(agregado, PadronBtree);
			}
			cont++;
		}
		fclose(archivo); //cierra el archivo
	}

	fin = time(NULL);
	tiemposBTREE[0] = difftime(fin, inicio);
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------BTREE cargado--------------------------------\n\n" << endl;
	system("pause");
	system("CLS");
}

//copia el sucesor del nodo que ser� borrado
void copySuccessor(NodoBtree* minodo, int pos) {
	NodoBtree* dummy;
	dummy = minodo->link[pos];

	for (; dummy->link[0] != NULL;)
		dummy = dummy->link[0];
	strcpy_s(minodo->llave[pos], dummy->llave[1]);

}

//remueve un valor de un nodo y reacomoda el arbol
void removeVal(NodoBtree* minodo, int pos) {
	int i = pos + 1;
	while (i <= minodo->count) {
		strcpy_s(minodo->llave[i - 1], minodo->llave[i]);
		minodo->link[i - 1] = minodo->link[i];
		i++;
	}
	minodo->count--;
}

//shift a la derecha
void doRightShift(NodoBtree* minodo, int pos) {
	NodoBtree* x = minodo->link[pos];
	int j = x->count;

	while (j > 0) {
		strcpy_s(x->llave[j + 1], x->llave[j]);
		x->link[j + 1] = x->link[j];
	}
	strcpy_s(x->llave[1], minodo->llave[pos]);
	x->link[1] = x->link[0];
	x->count++;

	x = minodo->link[pos - 1];
	strcpy_s(minodo->llave[pos], x->llave[x->count]);
	minodo->link[pos] = x->link[x->count];
	x->count--;
	return;
}

//shift a la izquierda
void doLeftShift(NodoBtree* minodo, int pos) {
	int j = 1;
	NodoBtree* x = minodo->link[pos - 1];

	x->count++;
	strcpy_s(x->llave[x->count], minodo->llave[pos]);
	x->link[x->count] = minodo->link[pos]->link[0];

	x = minodo->link[pos];
	strcpy_s(minodo->llave[pos], x->llave[1]);
	x->link[0] = x->link[1];
	x->count--;

	while (j <= x->count) {
		strcpy_s(x->llave[j], x->llave[j + 1]);
		x->link[j] = x->link[j + 1];
		j++;
	}
	return;
}

//Fusionar nodos
void UnirNodos(NodoBtree* minodo, int pos) {
	int j = 1;
	NodoBtree* x1 = minodo->link[pos], * x2 = minodo->link[pos - 1];

	x2->count++;
	strcpy_s(x2->llave[x2->count], minodo->llave[pos]);
	x2->link[x2->count] = minodo->link[0];

	while (j <= x1->count) {
		x2->count++;
		strcpy_s(x2->llave[x2->count], x1->llave[j]);
		x2->link[x2->count] = x1->link[j];
		j++;
	}

	j = pos;
	while (j < minodo->count) {
		strcpy_s(minodo->llave[j], minodo->llave[j + 1]);
		minodo->link[j] = minodo->link[j + 1];
		j++;
	}
	minodo->count--;
	free(x1);
}

//Ajusta el nodo dado
void AjustarNodo(NodoBtree* minodo, int pos) {
	if (!pos) {
		if (minodo->link[1]->count > MIN) {
			doLeftShift(minodo, 1);
		}
		else {
			UnirNodos(minodo, 1);
		}
	}
	else {
		if (minodo->count != pos) {
			if (minodo->link[pos - 1]->count > MIN) {
				doRightShift(minodo, pos);
			}
			else {
				if (minodo->link[pos + 1]->count > MIN) {
					doLeftShift(minodo, pos + 1);
				}
				else {
					UnirNodos(minodo, pos);
				}
			}
		}
		else {
			if (minodo->link[pos - 1]->count > MIN)
				doRightShift(minodo, pos);
			else
				UnirNodos(minodo, pos);
		}
	}
}

//borrar un valor del nodo
int BorrarDeNodo(const char* val, NodoBtree* minodo) {
	int pos, flag = 0;
	if (minodo) {
		if (strcmp(val, minodo->llave[1]) < 0) {
			pos = 0;
			flag = 0;
		}
		else {
			for (pos = minodo->count;
				(strcmp(val, minodo->llave[pos]) < 0 && pos > 1); pos--);
			if (strcmp(val, minodo->llave[pos]) == 0) {
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
		if (flag) {
			if (minodo->link[pos - 1]) {
				copySuccessor(minodo, pos);
				flag = BorrarDeNodo(minodo->llave[pos], minodo->link[pos]);
				if (flag == 0) {
					cout << "No existe en el B-Tree\n";
				}
			}
			else {
				removeVal(minodo, pos);
			}
		}
		else {
			flag = BorrarDeNodo(val, minodo->link[pos]);
		}
		if (minodo->link[pos]) {
			if (minodo->link[pos]->count < MIN)
				AjustarNodo(minodo, pos);
		}
	}
	return flag;
}

/* delete val from B-tree */
void borrado(const char* val, NodoBtree*& minodo) {
	NodoBtree* tmp;
	if (!BorrarDeNodo(val, minodo)) {
		return;
	}
	else {
		if (minodo->count == 0) {
			tmp = minodo;
			minodo = minodo->link[0];
			free(tmp);
		}
	}
	root = minodo;
	return;
}

/* search val in B-Tree */
void buscarBtree(const char* val, int* pos, NodoBtree* minodo) {
	if (!minodo) {
		return;
	}

	if (strcmp(val, minodo->llave[1]) < 0) {
		*pos = 0;
	}

	else {
		for (*pos = minodo->count;
			(strcmp(val, minodo->llave[*pos]) < 0 && *pos > 1); (*pos)--);
		if (strcmp(val, minodo->llave[*pos]) == 0) {
			cout << "----------------------------Votante encontrado-------------------------------" << endl;
			cout << "Votante: " << minodo->llave[*pos] << endl;
			return;
		}
	}

	buscarBtree(val, pos, minodo->link[*pos]);
	cout << "----------------------------Votante no encontrado----------------------------" << endl;
	return;
}

// B-Tree desplegar
void desplegar(NodoBtree* minodo) {
	if (minodo) {
		for (int i = 0; i < minodo->count; i++) {
			desplegar(minodo->link[i]);
			for (int j = 0; j < 119; j++) {
				cout << minodo->llave[i][j];
			}
			cout << "" << endl;
		}
		desplegar(minodo->link[minodo->count]);
	}
}


void resumenTiemposBTREE() {
	cout << "----------------------------Resumen de tiempos--------------------------------" << endl;
	cout << "Carga de padron: " << tiemposBTREE[0] << " segundos." << endl;
	cout << "Listado de votantes: " << tiemposBTREE[1] << " segundos." << endl;
	cout << "Ulitma busqueda de votante: " << tiemposBTREE[2] << " segundos." << endl;
	cout << "Liberacion de padron: " << tiemposBTREE[3] << " segundos." << endl;
	cout << "----------------------------Fin de resumen--------------------------------\n\n" << endl;
	system("pause");
	system("CLS");
}

void destruirBTREE(NodoBtree* nodo) {
	if (nodo) {
		for (int i = 0; i <= nodo->count; ++i) {
			destruirBTREE(nodo->link[i]);
		}
		delete nodo;
	}
}
