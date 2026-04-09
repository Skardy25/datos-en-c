#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;
typedef struct {
    Node *head;
    Node *tail;
    int len;
} List;

List *create_list(){
    List *l = malloc(sizeof(*l));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
    return l;
}
Node *create(int data){
    Node *n = malloc(sizeof(*n));
    if(n == NULL) return NULL;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void  insert_start(List *l, int valor){
    Node *n = create(valor);
    if(n == NULL) return;
    if(l->head == NULL){
        l->head = n;
        l->tail = n;
    }else{
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
    }
    l->len++;
}
void insert_tail(List *l, int data){
    Node *n =  create(data);
    if(n == NULL) return;
    if(l->tail == NULL){
        l->tail = n;
        l->head = n;
    }else{
        n->prev =l->tail;
        l->tail->next = n;
        l->tail = n;
    }
    l->len++;
}
void show_head(List *l){
    Node *n = l->head;
    while(n != NULL){
        printf("%d ", n->data);
        n = n->next;
    }
}
void show_tail(List *l){
    Node *tail = l->tail;
    while(tail != NULL){
        printf("%d ", tail->data);
        tail = tail->prev;
    }
}
void clean(List *l){
    for(int i= 0; i < l->len ; i++){
        Node *n = l->head;
        l->head = n->next;
        free(n);
    }
    free(l);
}

void delete_node(List *l, Node *n){
    if(l == NULL) return;
    if(n == NULL) return;
    if(n->prev != NULL){
        n->prev->next = n->next;
    }else{
        l->head = n->next;
    }
    if(n->next != NULL){
        n->next->prev = n->prev; 
    }else{
        l->tail = n->prev;
    }
    free(n);
    l->len--;
}
int main(){
    List *l = create_list();
    if(l == NULL) {
        printf("Error al crear la lista\n");
        return 1;
    }
    insert_start(l, 1);
    insert_start(l, 2);
    insert_start(l, 3);
    insert_start(l, 0);

    show_head(l);   // 0 -> 1 -> 2 -> 3 -> NULL
    show_tail(l);
    delete_node(l, l->head->next);
    show_head(l);
    printf("size: %d\n", l->len);   // 3

    clean(l);
    return 0;
}
