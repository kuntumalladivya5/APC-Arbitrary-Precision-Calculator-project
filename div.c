#include<stdio.h>
#include "calculator.h"

Status division(Node *head1, Node *head2, Node *tail2, Node **result_head, Node **result_tail)
{
    // Initialize the quotient list as empty
    *result_head = NULL;
    *result_tail = NULL;

    // Check whether the divisor is zero
    // Division by zero is not allowed
   if(is_zero(head2))
   {
     return c_failure;
   }

   // Create a temporary list to store the dividend
   Node *res1_head = NULL;
   Node *res1_tail = NULL;

   // Traverse the dividend from head to tail
   Node *temp = head1;

   while(temp != NULL)
   {
        // Copy each digit of the dividend into the temporary list
      if(insert_last(&res1_head, &res1_tail, temp->data) == c_failure)
      {
            // Free the partially created list if allocation fails
            free_list(&res1_head, &res1_tail);
            return c_failure;
      }

      // Move to the next digit
      temp= temp->next;

   }

   // Initialize the quotient to 0
   if(insert_last(result_head, result_tail, 0) == c_failure)
   {
        free_list(&res1_head, &res1_tail);
        return c_failure;
   }

   // Temporary list to store the subtraction result
   Node *temp_head = NULL;
   Node *temp_tail = NULL;

   // Temporary list to store the updated quotient
   Node *sum_head = NULL;
   Node *sum_tail = NULL;

   // Create a list containing the number 1
    // This is used to increment the quotient
   Node *one_head = NULL;
   Node *one_tail = NULL;

   if(insert_last(&one_head, &one_tail, 1) == c_failure)
   {
    free_list(&res1_head, &res1_tail);
    free_list(result_head, result_tail);
    free_list(&one_head, &one_tail);
    return c_failure;
   }

   // Continue while the remaining dividend is greater than
    // or equal to the divisor
   while(compare_numbers(res1_head, head2) >= 0)
   {
        // Subtract the divisor from the remaining dividend
        if(subtraction(res1_tail, tail2, &temp_head, &temp_tail) == c_failure)
        {
            // Free allocated lists if subtraction fails
            free_list(&temp_head, &temp_tail);
            free_list(&res1_head, &res1_tail);
            free_list(result_head, result_tail);
            free_list(&one_head, &one_tail);
            return c_failure;
        }
        // Free the previous remaining dividend
        free_list(&res1_head, &res1_tail);

        // Store the subtraction result as the new remainder
        res1_head = temp_head;
        res1_tail = temp_tail;

        // Reset temporary pointers
        temp_head = NULL;
        temp_tail = NULL;

        // Increment the quotient by 1
        if(addition(*result_tail, one_tail, &sum_head, &sum_tail) == c_failure)
        {
            // Free allocated lists if addition fails
            free_list(&res1_head, &res1_tail);
            free_list(&sum_head, &sum_tail);
            free_list(result_head, result_tail);
            free_list(&one_head, &one_tail);
            return  c_failure;
        }
        // Free the previous quotient
        free_list(result_head, result_tail);

        // Store the updated quotient
        *result_head = sum_head;
        *result_tail = sum_tail;

        // Reset temporary pointers
        sum_head = NULL;
        sum_tail = NULL;
   }
   // Free the helper lists after division is completed
   free_list(&one_head, &one_tail);
   free_list(&res1_head, &res1_tail);

   // Return success after calculating the quotient
   return c_success;
}