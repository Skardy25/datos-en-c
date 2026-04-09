// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    int valor;
    struct Nodo *siguiente;
} Nodo;
Nodo *crear_nodo(const int valor){
    Nodo *tmp = malloc(sizeof(*tmp));
    if(tmp == NULL){return NULL;}
    tmp->valor = valor;
    return tmp;
}
Nodo *insertar_inicio(Nodo *head ,const int valor){
    Nodo *n = crear_nodo(valor);
    if(n == NULL) return head;
    n->siguiente = head;
    return n;
}
Nodo *insertar_final(Nodo *head, int valor){
    Nodo *n = crear_nodo(valor);
    if(n == NULL) return head;
    if(head == NULL) return n;
    Nodo *actual = head;
    while(actual->siguiente != NULL){
        actual = actual->siguiente;
    }
    actual->siguiente = n;
    return head;
}
Nodo *eliminar(Nodo *head, int valor) {
    if(head == NULL) return NULL;
    // caso si el dato esta al inicio
    if(head->valor == valor){
        Nodo *tmp = head->siguiente;
        free(head);
        head = tmp;
        return head;
    }
    //caso si esta en el medio
    Nodo *actual = head;
    while(actual->siguiente != NULL){
        if(actual->siguiente->valor == valor){
            Nodo *tmp = actual->siguiente;
            actual->siguiente = tmp->siguiente;  // reconecta
            free(tmp);                            // ✅ libera
            break;                                // ✅ sal del loop
        }
        actual = actual->siguiente;
    }
    return head;
}
void imprimir(Nodo *head){
    Nodo *actual = head;
    while(actual != NULL){
        printf("%d -> ", actual->valor);
        actual = actual->siguiente;
    }
    printf("\n");
}
void liberar_lista(Nodo *head){
    while( head != NULL){
        Nodo *siguiente = head->siguiente;
        free(head);
        head = siguiente;
    }
}
int main(){
    Nodo *head = NULL;

    head = insertar_final(head, 1);
    head = insertar_final(head, 2);
    head = insertar_final(head, 3);
    head = insertar_final(head, 4);
    head = insertar_final(head, 5);

    imprimir(head);               // 1 -> 2 -> 3 -> 4 -> 5 -> NULL

    head = eliminar(head, 3);
    imprimir(head);               // 1 -> 2 -> 4 -> 5 -> NULL

    head = eliminar(head, 1);
    imprimir(head);               // 2 -> 4 -> 5 -> NULL

    head = eliminar(head, 5);
    imprimir(head);               // 2 -> 4 -> NULL

    liberar_lista(head);
    return 0;
}
