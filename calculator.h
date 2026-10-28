#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<stdlib.h>
#include "types.h"

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
}Node;

Status insert_last(Node **head, Node **tail, int data);

Status insert_first(Node **head, Node **tail, int data);

Status string_to_list(const char *str, Node **head, Node **tail);

void print_list(Node *head);

void free_list(Node **head, Node **tail);

Status addition(Node *tail1, Node *tail2, Node **result_head, Node **result_tail);

Status validate_number(const char *str);

void print_number(Node *head);

int compare_numbers(Node *head1, Node *head2);

Status subtraction(Node *tail1, Node *tail2, Node **result_head, Node **result_tail);

void remove_leading_zeros(Node **head, Node **tail);

Status multiplication(Node *tail1, Node *tail2, Node **result_head, Node **result_tail);

int is_zero(Node *head);

Status division(Node *head1, Node *head2, Node *tail2, Node **result_head, Node **result_tail);

Status modulus(Node *head1, Node *head2, Node *tail2, Node **result_head, Node **result_tail);

Status signed_add_sub(Node *head1, Node *tail1, Node *head2, Node *tail2, int sign1, int sign2, Node **result_head, Node **result_tail, int *result_sign);

#endif