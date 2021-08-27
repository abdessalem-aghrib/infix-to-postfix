#include "headers.h"

// functions
Stack *init_stack()
{
    Stack *new = malloc(sizeof(new));
    new->first = NULL;
    return new;
}

Stack *push(Stack *stack, char *symbol)
{
    if (stack == NULL)
        stack = init_stack();

    Node *new = malloc(sizeof(*new));

    if (new != NULL)
    {

        new->symbol = malloc(strlen(symbol) * sizeof(char));
        strcpy(new->symbol, symbol);

        new->next = stack->first;
        stack->first = new;
    }
    else
    {
        printf("\nMemory allocation problem ...!\n");
    }

    return stack;
}

char *pop(Stack *stack)
{
    if (stack != NULL)
    {
        char *symbol;
        Node *node = stack->first;

        if (stack->first != NULL)
        {
            symbol = malloc(strlen(node->symbol) * sizeof(char));
            strcpy(symbol, node->symbol);
            stack->first = node->next;
            free(node);
        }

        return symbol;
    }
    else
        return NULL;
}

void display_stack(Stack *stack)
{
    if (stack != NULL && stack->first != NULL)
    {
        Node *actuel = stack->first;

        while (actuel != NULL)
        {
            printf("%s", actuel->symbol);
            actuel = actuel->next;
        }
    }
    else
        printf("\nEmpty stack...!\n");
}

Stack *inverse_stack(Stack stack)
{
    Stack *temp = init_stack();
    while (is_stack_empty(&stack) == 0)
    {
        push(temp, pop(&stack));
    }
    return temp;
}

void display_inverse_stack(Stack stack)
{
    Stack *stack_temp = inverse_stack(stack);
    display_stack(stack_temp);
}

int is_stack_empty(Stack *stack)
{
    if (stack->first == NULL)
        return 1;
    return 0;
}

int is_operator(char *s)
{
    if (strcmp(s, "+") == 0 ||
        strcmp(s, "-") == 0 ||
        strcmp(s, "*") == 0 ||
        strcmp(s, "/") == 0 ||
        strcmp(s, ")") == 0 ||
        strcmp(s, "(") == 0)
        return 0;
    return 1;
}

int priority(char *x)
{
    if (strcmp(x, "(") == 0)
        return 0;
    if (strcmp(x, "+") == 0 || strcmp(x, "-") == 0)
        return 1;
    if (strcmp(x, "*") == 0 || strcmp(x, "\\") == 0)
        return 2;
    return 3;
}

Stack *infix_to_postfix(Stack *stack)
{

    // step 0: reverse the incoming stack
    stack = inverse_stack(*stack);

    // step 1: transform the expression into a postfix
    Stack *stack_op = init_stack(); // operands stack
    Stack *stack_final = init_stack();

    char *temp;

    while (is_stack_empty(stack) == 0)
    {
        temp = pop(stack);

        if (is_operator(temp) == 1)
        {
            // it's not an operator - push it in final stack
            push(stack_final, temp);
        }
        else if (strcmp(temp, "(") == 0)
        {
            // it's an opening parenthesis
            push(stack_op, temp);
        }
        else if (strcmp(temp, ")") == 0)
        {
            // it's a closing parenthesis
            while (strcmp((temp = pop(stack_op)), "(") != 0)
            {
                push(stack_final, temp);
            }
        }
        else
        {
            // it's an operator
            while (is_stack_empty(stack_op) == 0 &&
                   priority(stack_op->first->symbol) >= priority(temp))
            {
                //display_quad_arithm_expr[pos]=pop();
                //pos++;
                push(stack_final, pop(stack_op));
            }

            // push in operators stack
            push(stack_op, temp);
        }
    }

    while (is_stack_empty(stack_op) == 0)
    {
        push(stack_final, pop(stack_op));
    }

    return inverse_stack(*stack_final);
}

void display_quad_arithm_expr(Stack *stack)
{
    stack = infix_to_postfix(stack);
    Stack *stack_temp = init_stack();

    char *temp, *s, T[4] = "T1";
    int i = 0;

    while (is_stack_empty(stack) == 0)
    {
        temp = pop(stack);
        if (is_operator(temp))
            push(stack_temp, temp);
        else
        {
            s = pop(stack_temp);
            sprintf(T, "T%d", i);
            printf(" %3d - ( %s ,%3s ,%3s ,%s )\n", i, temp, pop(stack_temp), s, T);
            push(stack, T);
            while (is_stack_empty(stack_temp) == 0)
                push(stack, pop(stack_temp));
            i++;
        }
    }

    printf("\nT final : %s\n", T);
}
