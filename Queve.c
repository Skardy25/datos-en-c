// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char name[32];
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queve;

Node *create(char *data){
    Node *tmp = malloc(sizeof(*tmp));
    if(tmp == NULL) return NULL;
    strncpy(tmp->name, data, sizeof(tmp->name) -1);
    tmp->name[31] = '\0';
    tmp->next = NULL;
    return tmp;
}
Queve *create_queve(){
    Queve *tmp = malloc(sizeof(*tmp));
    if(tmp == NULL) return NULL;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return tmp;
}

void show(Queve *q){
    Node *tmp = q->head;
    while(tmp != NULL){
        printf("%s ", tmp->name);
        tmp = tmp->next;
    }
}
void enqueve(Queve *q, char *data){
    Node *new_node = create(data);
    if(new_node == NULL) return;
    
    if(q->size == 0){
        q->head = new_node;
        q->tail = new_node;
    }else{
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->size++;
}
char  *dequeve(Queve *q){
    if(q->size != 0){
        Node *tmp = q->head;
        char *copia_str = strndup(tmp->name, 32);
        q->head = q->head->next;
        if(q->head == NULL ) q->tail = NULL;
        q->size--;
        free(tmp);
        return copia_str;
    }
    return NULL;
}
char  *peek(Queve *q){
    if(q->size != 0){
        return q->head->name;
    }
    return NULL;
}
int is_empty(Queve *q){
    return q->size == 0;
}
void  liberar_queue(Queve *q){
    while(q->head != NULL){
        Node *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    free(q);
}
int main() {
    Queve *q = create_queve();
    if(q == NULL) return 1;
    enqueve(q, "Ana");
    enqueve(q, "Luis");
    enqueve(q, "Sofia");

    printf("Siguiente: %s\n", peek(q));      // Ana
    printf("Atendiendo: %s\n", dequeve(q));  // Ana
    printf("Atendiendo: %s\n", dequeve(q));  // Luis

    enqueve(q, "Pedro");
    printf("Siguiente: %s\n", peek(q));      // Sofia

    printf("En fila: %d\n", q->size);        // 2

    liberar_queue(q);
    return 0;
}
