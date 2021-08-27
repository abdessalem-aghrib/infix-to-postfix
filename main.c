
#include "implementations.c"

int main()
{
    Stack *my_stack = init_stack();
    Stack *my_quad_arithm_expr_stack = init_stack();

    // Infix expression :: ((a + b) * (c - d)) / ((e + f) * (g - h))

    char infix_expression[] = "((a + b) * (c - d)) / ((e + f) * (g - h))";
    char delim[] = " ";

    char *infix_expression_copy = malloc(sizeof(char) * strlen(infix_expression));
    strcpy(infix_expression_copy, infix_expression);


    char *ptr = strtok(infix_expression_copy, delim);
    while (ptr != NULL)
    {
        for (int i = 0; i < strlen(ptr); i++)
        {
            char str[2] = "\0"; /* gives {\0, \0} */
            str[0] = ptr[i];
            my_stack = push(my_stack, str);
            my_quad_arithm_expr_stack = push(my_quad_arithm_expr_stack, str);
        }
        
        ptr = strtok(NULL, delim);
    }

    printf("\n***********  INFIX EXPRESSION : \n\n[ %s ]\n\n", infix_expression);
    printf("***********  POSTFIX FORM OF THE INFIX EXPRESSION : \n\n");

    my_stack = infix_to_postfix(my_stack);
    display_stack(my_stack);

    printf("\n\n***********  QUADRUPLES OF THE POSTFIX EXPRESSION : \n\n");
    display_quad_arithm_expr(my_quad_arithm_expr_stack);

    return 0;
}
