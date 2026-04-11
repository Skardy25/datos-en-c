#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo *crear_nodo(int valor){
    Nodo *tmp = malloc(sizeof(*tmp));
    if(tmp == NULL) return NULL;
    tmp->valor = valor;
    tmp->izq = NULL;
    tmp->der = NULL;
    return tmp;
}
Nodo *insertar(Nodo *raiz, int valor){
    if(raiz == NULL) return crear_nodo(valor);
    if(valor < raiz->valor) {
        raiz->izq = insertar(raiz->izq ,valor);
    }
    else if(valor > raiz->valor) {
        raiz->der = insertar(raiz->der, valor);
    }
    return raiz;
}
Nodo *buscar(Nodo *raiz, int valor){
    if(raiz == NULL) return NULL;
    if(valor < raiz->valor){
        return buscar(raiz->izq, valor);
    }else if(valor > raiz->valor){
        return buscar(raiz->der, valor);
    }
    return raiz;
}
Nodo *sucesor(Nodo *raiz){
    raiz = raiz->der;
    while(raiz != NULL && raiz->izq != NULL){
        raiz = raiz->izq;
    }
    return raiz;
}

int   altura(Nodo *raiz){
    if(raiz == NULL) return 0;
    int der = altura(raiz->der);
    int izq = altura(raiz->izq);
    return (der > izq ? der : izq)+1;
    
}

Nodo *eliminar(Nodo *raiz, int valor){
    if(raiz == NULL) return NULL;
    if(valor < raiz->valor) {
        raiz->izq = eliminar(raiz->izq, valor);
    }
    else if(valor > raiz->valor){
        raiz->der = eliminar(raiz->der, valor);
    }else{
        if(raiz->izq == NULL){
            Nodo *tmp = raiz->der;
            free(raiz);
            return tmp;
        }
        if(raiz->der == NULL){
            Nodo *tmp = raiz->izq;
            free(raiz);
            return tmp;
        }
        Nodo *tmp = sucesor(raiz);
        raiz->valor = tmp->valor;
        raiz->der = eliminar(raiz->der, tmp->valor);
    }
    return raiz;
}
void liberar(Nodo *raiz){
    if(raiz == NULL) return;
    liberar(raiz->izq);
    liberar(raiz->der);
    free(raiz);
    
}
void inorden(Nodo *raiz){
    if(raiz == NULL) return;
    inorden(raiz->izq);
    printf("%d ",raiz->valor);
    inorden(raiz->der);
}

void preorden(Nodo *raiz){
    if(raiz == NULL) return;
    printf("%d ", raiz->valor);
    preorden(raiz->izq);
    preorden(raiz->der);
}
void postorden(Nodo *raiz){
    if(raiz == NULL) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    printf("%d ", raiz->valor);
}
int main(){
    Nodo *raiz = NULL;

    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 70);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 80);
    
    printf("Inorden:   "); inorden(raiz); printf("\n");
    printf("Preorden:   "); preorden(raiz); printf("\n");
    printf("Postorden:   "); postorden(raiz); printf("\n");
    
    raiz = eliminar(raiz, 30);  // nodo con dos hijos
    printf("Inorden   "); inorden(raiz); printf("\n");
    
    raiz = eliminar(raiz, 20);  // nodo hoja
    printf("Tras eliminar 20: "); inorden(raiz); printf("\n");
    liberar(raiz);
    return 0;
}


