#include<stdio.h>
#include "calculator.h"

Status modulus(Node *head1, Node *head2, Node *tail2, Node **result_head, Node **result_tail)
{
     // Initialize the result list as empty
    *result_head = NULL;
    *result_tail = NULL;

    // Check whether the divisor is zero
    // Modulus by zero is not allowed
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

     // Temporary list to store the subtraction result   
   Node *temp_head = NULL;
   Node *temp_tail = NULL;

   // Continue subtracting while the remaining value
    // is greater than or equal to the divisor
   while(compare_numbers(res1_head, head2) >= 0)
   {
          // Subtract the divisor from the current remainder
        if(subtraction(res1_tail, tail2, &temp_head, &temp_tail) == c_failure)
        {
               // Free allocated lists if subtraction fails
            free_list(&temp_head, &temp_tail);
            free_list(&res1_head, &res1_tail);
            return c_failure;
        }

        // Free the previous remainder list
        free_list(&res1_head, &res1_tail);

        // Store the subtraction result as the new remainder
        res1_head = temp_head;
        res1_tail = temp_tail;

        // Reset temporary pointers for the next iteration
        temp_head = NULL;
        temp_tail = NULL;

   }    
         // Transfer the final remainder list to the result 
        *result_head = res1_head;
        *result_tail = res1_tail;

        // Reset local pointers because the result now owns the list
        res1_head = NULL;
        res1_tail = NULL;

   // Return success after calculating the remainder
   return c_success;
}