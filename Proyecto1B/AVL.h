#pragma once
#include "Lista.h"

double tiemposAVL[4];

struct NodoAVL {
    char llave[120];
    struct NodoAVL* izq;
    struct NodoAVL* derecha;
    struct NodoAVL* padre; 
    int altura;
};

//obtiene el maximo de dos numeros
int maximo(int a, int b);

//obtiene la altura del arbol
int altura(NodoAVL*& N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

int maximo(int a, int b)
{
    return (a > b) ? a : b;
}

NodoAVL* nuevoNodo(NodoAVL*& Nodo, NodoAVL* padre, char llave[120]) {
    Nodo = new(NodoAVL);
    strncpy_s(Nodo->llave, llave, 120);
    Nodo->izq = NULL;
    Nodo->derecha = NULL;
    Nodo->padre = padre; // Establece el padre del nuevo nodo
    Nodo->altura = 1;  // Nuevo nodo es agregado como hoja
    return(Nodo);
}

NodoAVL* RotarDerecha(NodoAVL*& y)
{
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->derecha;

    // hace rotacion
    x->derecha = y;
    y->izq = T2;

    // actualiza alturas
    y->altura = maximo(altura(y->izq), altura(y->derecha)) + 1;
    x->altura = maximo(altura(x->izq), altura(x->derecha)) + 1;

    // retorna nueva raiz
    return x;
}

NodoAVL* RotarIzquierda(NodoAVL*& x)
{
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izq;

    // hace rotacion
    y->izq = x;
    x->derecha = T2;

    //  actualiza alturas
    x->altura = maximo(altura(x->izq), altura(x->derecha)) + 1;
    y->altura = maximo(altura(y->izq), altura(y->derecha)) + 1;

    // retorna nueva raiz
    return y;
}

// obtiene balance
int obtenerbalance(NodoAVL*& N)
{
    if (N == NULL)
        return 0;
    return altura(N->izq) - altura(N->derecha);
}

// Función para insertar un nodo en el árbol AVL
NodoAVL* insertarAVL(NodoAVL*& Nodo, NodoAVL* padre, char agregar[120]) {
    if (Nodo == nullptr) {
        return nuevoNodo(Nodo, padre, agregar);
    }

    int comparacion = strncmp(agregar, Nodo->llave, 9);

    if (comparacion < 0) {
        Nodo->izq = insertarAVL(Nodo->izq, Nodo, agregar); // Pasa Nodo como padre
    }
    else if (comparacion > 0) {
        Nodo->derecha = insertarAVL(Nodo->derecha, Nodo, agregar); // Pasa Nodo como padre
    }
    else {
        // No se permiten llaves iguales
        return Nodo;
    }

    Nodo->altura = 1 + maximo(altura(Nodo->izq), altura(Nodo->derecha));

    int balance = obtenerbalance(Nodo);

    // 4 casos para un árbol desbalanceado

    // izq izq 
    if (balance > 1 && strncmp(agregar, Nodo->izq->llave, 9) < 0)
        return RotarDerecha(Nodo);

    // derecha derecha 
    if (balance < -1 && strncmp(agregar, Nodo->derecha->llave, 9) > 0)
        return RotarIzquierda(Nodo);

    // izq derecha
    if (balance > 1 && strncmp(agregar, Nodo->izq->llave, 9) > 0) {
        Nodo->izq = RotarIzquierda(Nodo->izq);
        return RotarDerecha(Nodo);
    }

    // derecha izq 
    if (balance < -1 && strncmp(agregar, Nodo->derecha->llave, 9) < 0) {
        Nodo->derecha = RotarDerecha(Nodo->derecha);
        return RotarIzquierda(Nodo);
    }

    return Nodo;
}

NodoAVL* buscarAVL(NodoAVL* Raiz, const char* cualllave) {
    if (Raiz == NULL) {
        return NULL;                            //Si el Arbol esta vacio, retorna NULL
    }
    else {
        int comparacion = strncmp(cualllave, Raiz->llave, 9);
        if (comparacion == 0) return Raiz;                                      //Si la llave es igual al Nodo Raiz, retorna el Nodo Raiz
        else if (comparacion < 0) return buscarAVL(Raiz->izq, cualllave);       //Si la llave es menor, busca en el Hijo Izquierdo
        else return buscarAVL(Raiz->derecha, cualllave);                        //Si la llave es mayor, busca en el Hijo Derecho
    }
}

void listarAVL(NodoAVL* Raiz) {
    if (Raiz != NULL) {
        listarAVL(Raiz->derecha);
        printf("%s\n", Raiz->llave);
        listarAVL(Raiz->izq);
    }
}

NodoAVL* cargarAVL(NodoAVL*& PadronAVL) {
    int cont = 1;
    time_t inicio, fin;
    inicio = time(NULL);
    FILE* archivo;

    cout << "\n\n----------------------------Cargando AVL--------------------------------" << endl;

    fopen_s(&archivo, "PADRON_COMPLETO.txt", "r");                      // Abre el archivo del padron electoral con read.
    if (NULL == archivo) {
        printf("No se pudo abrir el archivo");
    }
    else {
        char agregado[119];	                                            // Longitud de toda la cadena de un votante
        NodoAVL* padre = nullptr;                                       // Puntero al padre, inicialmente nulo
        while (fgets(agregado, 119, archivo) != NULL) {                 // Evita que se desborde con basura al leer el fin de la cadena.
            agregado[strcspn(agregado, "\n")] = '\0';
            if (cont % 2 != 0) {                                        // Esta condicion evita que se repitan los votantes ya que va de dos en dos.
                PadronAVL = insertarAVL(PadronAVL, padre, agregado);    // Pasamos el padre al insertarAVL
            }
            cont++;
        }
        fclose(archivo); // Cierra el archivo
    }

    fin = time(NULL);
    tiemposAVL[0] = difftime(fin, inicio);
    printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
    cout << "----------------------------AVL cargado--------------------------------\n\n" << endl;
    system("pause");
    system("CLS");

    return PadronAVL;
}

void destruirAVL(NodoAVL*& root)
{
    if (root != NULL)
    {
        destruirAVL(root->izq);
        destruirAVL(root->derecha);
        delete root;
        root = NULL;
    }
}

void resumenTiemposAVL() {
    cout << "----------------------------Resumen de tiempos----------------------------" << endl;
    cout << "Carga de padron: " << tiemposAVL[0] << " segundos." << endl;
    cout << "Listado de votantes: " << tiemposAVL[1] << " segundos." << endl;
    cout << "Ulitma busqueda de votante: " << tiemposAVL[2] << " segundos." << endl;
    cout << "Liberacion de padron: " << tiemposAVL[3] << " segundos." << endl;
    cout << "----------------------------Fin de resumen--------------------------------\n\n" << endl;
}