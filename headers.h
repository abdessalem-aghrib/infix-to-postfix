#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// structers
typedef struct Node Node;
struct Node {
    char *symbol;
    Node *next;
};

typedef struct Stack Stack;
struct Stack{
    Node *first;
};

// prototypes
Stack* init_stack();
Stack * push(Stack *stack, char *symbol);
char* pop(Stack *stack);
void display_stack(Stack *stack);
Stack* inverse_stack(Stack Stack);
void display_inverse_stack(Stack stack);
int is_stack_empty(Stack *stack);
int is_operator(char *s);
int priority(char *x);
Stack* infix_to_postfix(Stack *stack);
void display_quad_arithm_expr(Stack *stack);