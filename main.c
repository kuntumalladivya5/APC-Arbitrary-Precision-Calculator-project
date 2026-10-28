/*
 *Name : K.Divya
 * Project: Arbitrary Precision Calculator (APC)
 * Description: Accepts two numbers and an arithmetic operator
 *              through command-line arguments, performs the
 *              selected operation, and displays the result.
 */

#include<stdio.h>
#include "calculator.h"


int main(int argc, char *argv[])
{
    int sign1 = 1;
    int sign2 =1;
    int result_sign = 1;

    // Determine the sign of each input number.
    if(argv[1][0] == '-')
        sign1 = -1;

    if(argv[3][0] == '-')
        sign2 = -1;

    /* Initialize linked lists for the input numbers. */
    Node *head1 = NULL;
    Node *tail1 = NULL;

    Node *head2 = NULL;
    Node *tail2 = NULL;

    /* Initialize the linked list for the operation result. */
    Node *result_head = NULL;
    Node *result_tail = NULL;

    /* Check whether the required command-line arguments are provided. */
    if(argc != 4)
    {
        printf("Usage: ./apc number1 operator number2\n");
        return c_failure;
    }

    /* Validate the first input number. */
    if(validate_number(argv[1]) == c_failure)
    {
        printf("Error: Invalid first number\n");
        return c_failure;
    }

    /* Validate the second input number. */
    if(validate_number(argv[3]) == c_failure)
    {
        printf("Error: Invalid second number\n");
        return c_failure;
    }

    /* Convert the first input string into a doubly linked list. */
    if(string_to_list(argv[1], &head1, &tail1) == c_failure)
    {
        printf("Invalid first number\n");
        return c_failure;
    }

    /* Convert the second input string into a doubly linked list. */
    if(string_to_list(argv[3], &head2, &tail2) == c_failure)
    {
        printf("invalid second number\n");
        free_list(&head1, &tail1);
        return c_failure;
    }

   /* Select the arithmetic operation using the given operator. */
    switch(argv[2][0])
    {
        case '+':
        case '-':
        {
            int effective_sign2 = sign2;

            // Subtraction is addition with the opposite sign.
            if(argv[2][0] == '-')
            {
                effective_sign2 = -sign2;
            }

            if(signed_add_sub(head1, tail1, head2, tail2, sign1, effective_sign2, &result_head, &result_tail, &result_sign) == c_failure)
            {
                printf("Addition/Subtraction failed\n");
                break;
            }

            printf("Result: ");

            if(result_sign == -1)
            {
                printf("-");
            }

            print_number(result_head);
            break;
        }


        case 'x':

            /* Multiply the numbers using partial products. */
            if(multiplication(tail1, tail2, &result_head, &result_tail) == c_failure)
            {
                printf("Multiplication failed\n");
                break;
            }
            result_sign = sign1 * sign2;

            // Zero should not have a negative sign.
            if(is_zero(result_head))
            {
                result_sign = 1;
            }

            printf("Result: ");

            if(result_sign == -1)
            {
                printf("-");
            }

            print_number(result_head);
            break;
        
        case '/':

            /* Calculate the integer quotient. */
            if(division(head1, head2, tail2, &result_head, &result_tail) == c_failure)
            {
                printf("Divivsion failed\n");
                break;
            }
            result_sign = sign1 * sign2;

            if(is_zero(result_head))
            {
                result_sign = 1;
            }

            printf("Result: ");

            if(result_sign == -1)
            {
                printf("-");
            }

            print_number(result_head);
            break;

        case '%':

            /* Calculate the remainder after integer division. */
            if(modulus(head1, head2, tail2, &result_head, &result_tail) == c_failure)
            {
                printf("Divivsion failed\n");
                break;
            }
                result_sign = sign1 * sign2;

            if(is_zero(result_head))
            {
                result_sign = 1;
            }

            printf("Result: ");

            if(result_sign == -1)
            {
                printf("-");
            }
            print_number(result_head);
            break;

        default:

            /* Handle operators that are not supported. */
            printf("Unsupported operator\n");
            break;    
    }

    /* Release all allocated linked-list memory before exiting. */
    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&result_head, &result_tail);
    
    return c_success;
}