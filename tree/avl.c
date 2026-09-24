#include <stdlib.h> 
#include <stdio.h>
#include <stdint.h>

struct Nodo {
  int dato;
  struct Nodo *izq;
  struct Nodo *der;
  int altura;
};

int Altura(struct Nodo *raiz) {
  if (raiz == NULL) return 0;
  return raiz->altura;
}

int Maximo(int a, int b) {
  return (a > b) ? a : b;
}

int ObtenerFE(struct Nodo *raiz) {
  if (raiz == NULL) return 0;
  return Altura(raiz->izq) - Altura(raiz->der);
}

struct Nodo *CrearNodo(int valor) {
  struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
  nuevo->dato = valor;
  nuevo->der = NULL;
  nuevo->izq = NULL;
  nuevo->altura = 1; // La altura inicial de un nodo hoja es 1
  return nuevo;
}

struct Nodo *rotarDerecha(struct Nodo *raiz) {
  struct Nodo *x = raiz->izq;
  struct Nodo *y = x->der;

  // Realizar la rotacion
  x->der = raiz;
  raiz->izq = y;

  // Actualizar alturas
  raiz->altura = Maximo(Altura(raiz->izq), Altura(raiz->der)) + 1;
  x->altura = Maximo(Altura(x->izq), Altura(x->der)) + 1;

  return x;
}

struct Nodo *rotarIzquirda(struct Nodo *raiz) {
  struct Nodo *x = raiz->der;
  struct Nodo *y = x->izq;

  x->izq = raiz;
  raiz->der = y;

  // Actualizar alturas
  raiz->altura = Maximo(Altura(raiz->izq), Altura(raiz->der)) + 1;
  x->altura = Maximo(Altura(x->izq), Altura(x->der)) + 1;

  return x;
}

struct Nodo *Insertar(struct Nodo *raiz, int valor) {
  if (raiz == NULL) {
    return CrearNodo(valor);
  }

  if (valor < raiz->dato) { 
    raiz->izq = Insertar(raiz->izq, valor);
  } else if (valor > raiz->dato) {
    raiz->der = Insertar(raiz->der, valor);
  } else {
    return raiz; // No se permiten duplicados
  }

  // Actualizar altura
  raiz->altura = 1 + Maximo(Altura(raiz->izq), Altura(raiz->der));
  
  int factor_FE = ObtenerFE(raiz);

  // Caso LL: Rotacion Simple Derecha
  if (factor_FE > 1 && valor < raiz->izq->dato) {
    return rotarDerecha(raiz);
  }
  // Caso RR: Rotacion Simple Izquierda (Corregido: factor_FE < -1)
  if (factor_FE < -1 && valor > raiz->der->dato) {
    return rotarIzquirda(raiz);
  }
  // Caso LR: Doble Izquierda-Derecha
  if (factor_FE > 1 && valor > raiz->izq->dato) {
    raiz->izq = rotarIzquirda(raiz->izq);
    return rotarDerecha(raiz);
  }
  // Caso RL: Doble Derecha-Izquierda
  if (factor_FE < -1 && valor < raiz->der->dato) {
    raiz->der = rotarDerecha(raiz->der);
    return rotarIzquirda(raiz);
  }

  return raiz;
}

void preOrder(struct Nodo *raiz) {
  if (raiz != NULL) {
    printf(" - %i -", raiz->dato); // Imprime primero el nodo actual (Raíz)
    preOrder(raiz->izq);
    preOrder(raiz->der);
  }
}

void liberarArbol(struct Nodo *raiz) {
  if (raiz == NULL) return;
  liberarArbol(raiz->izq);
  liberarArbol(raiz->der);
  free(raiz);
}

int main(void) {
  struct Nodo *raiz = NULL; // Inicialización correcta a NULL

  raiz = Insertar(raiz, 10);
  raiz = Insertar(raiz, 20);
  raiz = Insertar(raiz, 30);
  raiz = Insertar(raiz, 40);
  raiz = Insertar(raiz, 50);
  raiz = Insertar(raiz, 25);

  printf("Recorrido Pre-Orden del Arbol AVL:\n");
  preOrder(raiz);
  printf("\n");

  liberarArbol(raiz);
  return EXIT_SUCCESS;
}
