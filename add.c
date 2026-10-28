#include<stdio.h>
#include "calculator.h"

Status addition(Node *tail1, Node *tail2, Node **result_head, Node **result_tail)
{
    // Initialize the result list as empty
    *result_head = NULL;
    *result_tail = NULL;

    // Create temporary pointers to traverse both numbers from right to left
    Node *temp1 = tail1;
    Node *temp2 = tail2;
    int carry = 0;
    int sum;
  
    // Continue until both numbers and the carry are processed
    while(temp1 != NULL || temp2 != NULL || carry != 0)
    {
        // Start the sum with the carry from the previous digit
        sum = carry;

         // Add the current digit of the first number
        if(temp1 != NULL)
        {
            sum = sum + temp1->data;
            temp1 = temp1->prev;
        }

        // Add the current digit of the second number
        if(temp2 != NULL)
        {
            sum = sum + temp2->data;
            temp2 = temp2->prev;
        }

        // Calculate the carry for the next digit
        carry = sum / 10;

        // Extract the current result digit
        int digit = sum % 10;

        // Insert the result digit at the beginning of the result list
        if(insert_first(result_head, result_tail, digit) == c_failure)
        {
            // Free the partially created result list if allocation fails
            free_list(result_head, result_tail);
            return c_failure;
        }
    }

    // Remove unnecessary leading zeros from the result
    remove_leading_zeros(result_head, result_tail);

    // Return success after completing the addition
    return c_success;
}