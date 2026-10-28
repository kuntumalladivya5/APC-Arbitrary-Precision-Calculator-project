#include<stdio.h>
#include "calculator.h"

Status signed_add_sub(Node *head1, Node *tail1, Node *head2, Node *tail2, int sign1, int sign2, Node **result_head, Node **result_tail, int *result_sign)
{
    int comparison;

    *result_head = NULL;
    *result_tail = NULL;
    *result_sign = 1;
    // If both signs match, add the magnitudes.
    if(sign1 == sign2)
    {
        if(addition(tail1, tail2, result_head, result_tail) == c_failure)
        {
            return c_failure;
        }

        *result_sign = sign1;
        // The caller can use sign1 as the result sign.
        return c_success;
    }

    // For different signs, compare the magnitudes.
    comparison = compare_numbers(head1, head2);

    // Equal magnitudes produce zero.
    if(comparison == 0)
    {
        return insert_last(result_head, result_tail, 0);
    }

    // Subtract the smaller magnitude from the larger.
    if(comparison > 0)
    {
        if(subtraction(tail1, tail2, result_head, result_tail) == c_failure)
        {
            return c_failure;
        }

        *result_sign = sign1;
    }
    else
    {
        if(subtraction(tail2, tail1, result_head, result_tail) == c_failure)
        {
            return c_failure;
        }

        *result_sign = sign2;
    }

    return c_success;
}