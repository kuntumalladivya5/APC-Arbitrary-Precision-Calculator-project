#include <stdio.h>
#include "calculator.h"


Status multiplication(Node *tail1, Node *tail2, Node **result_head, Node **result_tail)
{
    // Temporary list to store the sum of partial products
    Node *sum_head = NULL;
    Node *sum_tail = NULL;

    // Temporary pointers to traverse both numbers
    Node *temp1 = tail1;
    Node *temp2 = tail2;
    
    int digit;
    int carry = 0;
    int product = 0;

    // List to store the partial product of each digit
    Node *partial_head = NULL;
    Node *partial_tail = NULL;

    // Initialize the final result list as empty
    *result_head = NULL;
    *result_tail = NULL;

    // Tracks the number of zeros to append to each partial product
    int position = 0;

    // Traverse the second number from right to left
    while(temp2 != NULL)
    {
        // Start from the last digit of the first number
        temp1 = tail1;
        carry = 0;

        // Multiply the current digit of the second number
        // with every digit of the first number

        while(temp1 != NULL)
        {
            // Multiply the digits and add the previous carry
            product = (temp1->data * temp2->data) + carry;

            // Extract the current result digit
            digit = product % 10;

            // Calculate the carry for the next multiplication
            carry = product/10;
            
                // Insert the digit at the beginning of the partial product
                if(insert_first(&partial_head, &partial_tail, digit) == c_failure)
                {
                    // Free allocated lists if memory allocation fails
                    free_list(&partial_head, &partial_tail);
                    free_list(result_head, result_tail);
                    return c_failure;
                }
            
            // Move to the previous digit of the first number
            temp1 = temp1->prev;
        }

        // Insert any remaining carry into the partial product
        if(carry > 0)
        {
            if(insert_first(&partial_head, &partial_tail, carry) == c_failure)
            {
                // Free allocated lists if memory allocation fails
                free_list(&partial_head, &partial_tail);
                free_list(result_head, result_tail);
                return c_failure;
            }
        }
        // Append zeros according to the digit's position
        // First partial product gets 0 zeros, next gets 1, and so on
        for(int i = 0; i < position; i++)
        {
            if(insert_last(&partial_head, &partial_tail, 0) == c_failure)
            {
                 // Free allocated lists if memory allocation fails
                free_list(&partial_head, &partial_tail);
                free_list(result_head, result_tail);
                return c_failure;
            }
        }

        // If this is the first partial product, use it as the result
        if(*result_head == NULL)
        {
            *result_head = partial_head;
            *result_tail = partial_tail;

            // Transfer ownership of the list to the result
            partial_head = NULL;
            partial_tail = NULL;
        }
        else
        {
            // Add the current partial product to the accumulated result
            if(addition(*result_tail, partial_tail, &sum_head, &sum_tail) == c_failure)
            {
                // Free allocated lists if addition fails
                free_list(&sum_head, &sum_tail);
                free_list(&partial_head, &partial_tail);
                free_list(result_head, result_tail);
                return c_failure;
            }

            // Free the old result and partial product lists
            free_list(result_head, result_tail);
            free_list(&partial_head, &partial_tail);

            // Store the newly calculated sum as the result
            *result_head = sum_head;
            *result_tail = sum_tail;

            // Reset temporary pointers
            sum_head = NULL;
            sum_tail = NULL;

        }
        // Move to the next position for the next partial product
        position++;

        // Move to the previous digit of the second number
        temp2 = temp2->prev;
    }
    // Remove unnecessary leading zeros from the final result
    remove_leading_zeros(result_head, result_tail);

     // Return success after multiplication is completed
    return c_success;
}