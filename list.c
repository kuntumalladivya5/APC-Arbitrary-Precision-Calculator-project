#include<stdio.h>
#include<stdlib.h>
#include "calculator.h"

// Creates a new node and inserts it at the end of the doubly linked list.
Status insert_last(Node **head, Node **tail, int data)
{
    Node *new = malloc(sizeof(Node));
    
    // Check whether memory allocation was successful.
    if(new == NULL)
    {
        return c_failure;
    }
    // Initialize the new node.
    new->prev = *tail;
    new->data = data;
    new->next = NULL;

    // If the list is empty, the new node becomes both head and tail.
    if(*head == NULL && *tail == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        // Link the new node after the current tail.
        (*tail)->next = new;
        *tail = new;
    }
    return c_success;
}

//Creates a new node and inserts it at the beginning of the doubly linked list.
Status insert_first(Node **head, Node **tail, int data)
{

    Node *new = malloc(sizeof(Node));

    // Check whether memory allocation was successful.
    if(new == NULL)
        return c_failure;

    // Initialize the new node.
    new->data = data;
    new->next = *head;
    new->prev = NULL;

    // If the list is empty, the new node becomes both head and tail.
    if(*head == NULL && *tail == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        // Link the new node before the current head.
        (*head)->prev = new;
        *head = new;
    }
    return c_success;
}

//Displays all elements of the doubly linked list from head to tail.
void print_list(Node *head)
{
    // Handle an empty list.
    if(head == NULL)
    {
        printf("Info : List is empty\n");
    }
    else
    {
    // Traverse the list and print each node's data.    
    while(head)
    {
        printf("%d" , head -> data);
        head = head->next;
        if(head)
        printf(" <-> ");
    }
    printf("\n");
    }
}

// Releases the memory occupied by all nodes and resets the head and tail pointers.
void free_list(Node **head, Node **tail)
{
    Node *temp = *head;
    Node *next;

    // Free each node while preserving the next node's address.
    while(temp != NULL)
    {
        next=temp->next;
        free(temp);
        temp = next;
    }

    // Free each node while preserving the next node's address.
    *head = NULL;
    *tail = NULL;
}

//  Converts a numeric string into a doubly linked list, storing each decimal digit in a separate node.
Status string_to_list(const char *str, Node **head, Node **tail)
{
    int i = 0;

     // Validate the input string and pointer arguments.
    if(str == NULL || head == NULL || tail == NULL || str[0] == '\0')
    {
        return c_failure;
    }

    // Skip the sign; store only the digits in the linked list.
    if(str[0] == '+' || str[0] == '-')
    {
        i = 1;
    }

    // Reject a string containing only the minus sign.
    if(str[i] == '\0')
    {
        return c_failure;
    }

    // Validate each character and insert its digit into the list.
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
        {
            // Release any nodes created before invalid input was found.
            free_list(head, tail);
            return c_failure;
        }
    
     // Convert the character digit into its integer value.
     int digit = str[i] - '0';

     // Append the digit to the end of the list.
     if(insert_last(head, tail, digit) == c_failure)   
     {
        // Clean up allocated nodes if insertion fails.
        free_list(head, tail);
        return c_failure;
     }

     i++;
    }

     // Normalize the number by removing unnecessary leading zeros.
    remove_leading_zeros(head, tail);

    return c_success;
}

// Checks whether the input string contains only digits.
Status validate_number(const char *str)
{
    int i=0;

    // Reject a NULL pointer or an empty string.
    if(str == NULL || str[0] == '\0')
    {
        return c_failure;
    } 

    // Allow an optional minus sign at the beginning.
    if(str[0] == '+' || str[0] == '-')
    {
        i = 1;
    }

    // A minus sign alone is not a valid number.
    if(str[i] == '\0')
    {
        return c_failure;
    }

    // Check every character for a decimal digit.
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
        {
            return c_failure;
        }
        i++;
    }
    return c_success;
}

//Prints the digits stored in the list consecutively, representing the complete number.
void print_number(Node *head)
{
    // Handle a NULL list.
    if(head == NULL)
    {
        printf("List is NULL\n");
        return;
    }

    // Print digits from the most significant to the least significant
    while (head != NULL)
    {
        printf("%d", head->data);
        head=head->next;
    }
    printf("\n");
}


//Compares two non-negative integers represented by doubly linked lists.
int compare_numbers(Node *head1, Node *head2)
{
    int count1 = 0;
    int count2 = 0;

    Node *temp1 = head1;
    Node *temp2 = head2;

    // Count the number of digits in the first number.
    while(temp1 != NULL )
    {
        count1++;
        temp1 = temp1->next; 
    }

    // Count the number of digits in the second number.
    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    // A number with more digits is greater, assuming no leading zeros.
    if(count1 >count2)
        return 1;

    if(count1 < count2)
        return -1;

    // If digit counts match, compare corresponding digits from the head.
    temp1 = head1;
    temp2 = head2;

    while(temp1 != NULL && temp2 != NULL)
    {
        if(temp1->data > temp2->data)
        {
            return 1;
        }
        if(temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // All corresponding digits match.
    return 0;
}

// Removes unnecessary zeros from the beginning of the list while preserving one zero for the value 0.
void remove_leading_zeros(Node **head, Node **tail)
{
    // Remove leading zeros, but keep at least one node.
    while(*head != NULL && (*head)->next != NULL && (*head)->data == 0)
    {
        Node *temp = *head;

        // Move the head to the next node and detach the old head.
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    // Keep the tail pointer consistent if the list becomes empty.
    if(*head == NULL)
    {
        *tail = NULL;
    }
}

// Checks whether every digit in the list is zero.
int is_zero(Node *head)
{
   Node *temp = head; 

   // If any digit is non-zero, the number is not zero.
   while(temp != NULL)
   {
        if(temp->data != 0)
        {
            return 0;
        }
        temp = temp->next;
   }

   // All digits are zero, or the list is empty.
   return 1;
}