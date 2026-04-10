#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char data;
    struct Node *next;
}Node;

typedef struct {
    Node * top;
    int size;
} Stack;

Stack *crear_stack(){
    Stack *n = malloc(sizeof(*n));
    if(n == NULL) return NULL;
    n->top = NULL;
    n->size = 0;
    return n;
}
Node *create_node(const char value){
    Node *tmp = malloc(sizeof(*tmp));
    if(tmp == NULL) return NULL;
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}
int is_empty(Stack *s){
    if(s == NULL) return 1;
    return s->size == 0;
}
void push(Stack *s, char valor){
    Node *tmp = create_node(valor);
    if(s == NULL || tmp == NULL) return;
    tmp->next = s->top;
    s->top = tmp;
    s->size++;
}
char pop(Stack *s){
    if(s == NULL || is_empty(s)) return ' ';
    Node *tmp = s->top;
    char  val = tmp->data;
    s->top    = tmp->next;
    free(tmp);
    s->size--;
    return val;
}

char peek(Stack *s){
    if(s == NULL) return ' ';
    char tmp = ' ';
    if(!is_empty(s)){
        tmp = s->top->data;
    }
    return tmp;
}
void liberar_stack(Stack *s){
    if(s == NULL) return;
    while(s->top != NULL){
        Node *tmp = s->top;
        s->top = tmp->next;
        free(tmp);
    }
}
void show(Stack *s){
    if(s == NULL) return ;
    Node *head = s->top;
    while(head != NULL){
        printf("%c \n", head->data);
        head = head->next;
    }
}

int balanceado(const char *expr){
    if(strlen(expr) == 0) return 1;
    Stack *s = crear_stack();
    for(int i = 0; expr[i] != '\0'; i++){
        if(expr[i]==')' || expr[i]=='}' || expr[i]==']'){
            char top = peek(s);
            if(top == ' ') { liberar_stack(s); free(s); return 0; }
            if((top=='(' && expr[i]==')')  ||
               (top=='[' && expr[i]==']')  ||
               (top=='{' && expr[i]=='}')) pop(s);
        } else {
            push(s, expr[i]);
        }
    }
    int ok = is_empty(s);
    liberar_stack(s);
    free(s);
    return ok;
}

int main(){
    printf("%d\n", balanceado("({[]})"));   // 1
    printf("%d\n", balanceado("({[}])"));   // 0
    printf("%d\n", balanceado("((("));      // 0
    printf("%d\n", balanceado(""));         // 1
    printf("%d\n", balanceado("()[]{}"));   // 1
    return 0;
}

