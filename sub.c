#include<stdio.h>
#include "calculator.h"

Status subtraction(Node *tail1, Node *tail2, Node **result_head, Node **result_tail)
{
    // Create temporary pointers to traverse both numbers from right to left
    Node *temp1 = tail1;
    Node *temp2 = tail2;

    int borrow = 0;

     // Initialize the result list as empty
    *result_head = NULL;
    *result_tail = NULL;

    int digit1; //current digit from the first number
    int digit2; // current digit from the second number
    int digit; // calculated result digit

    // Continue until all digits of both numbers are processed
    while(temp1 != NULL || temp2 != NULL)
    {
        // Get the current digit from the first number
        // If no digit is available, use 0
        if(temp1 != NULL)
            digit1 = temp1->data;
        else
            digit1 = 0;

        // Get the current digit from the second number
        // If no digit is available, use 0
        if(temp2 != NULL)
            digit2 = temp2->data;
        else
            digit2 = 0;

        // Subtract the borrow from the previous digit calculation
        digit1 = digit1 - borrow;

        // Check whether borrowing is required
        if(digit1 < digit2)
        {
            // Borrow 1 from the next higher digit
            digit1 = digit1 + 10;
            borrow = 1;
        }
        else
        {
            // No borrowing is required
            borrow = 0;
        }
        // Calculate the current result digit
        digit = digit1 - digit2;

        // Insert the result digit at the beginning of the result list
        if(insert_first(result_head, result_tail, digit) == c_failure)
        {
            // Free the partially created result list if allocation fails
            free_list(result_head, result_tail);
            return c_failure;
        }

        // Move to the previous digit in the first number
        if(temp1 != NULL)
            temp1 = temp1->prev;

        // Move to the previous digit in the second number
        if(temp2 != NULL)
            temp2 = temp2->prev;

    }

    // Remove unnecessary leading zeros from the result
    remove_leading_zeros(result_head, result_tail);
    
    // Return success after completing the subtraction
    return c_success;
}