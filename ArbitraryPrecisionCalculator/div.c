#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    /* Check for NULL or zero divisor */
    if (head2 == NULL || (head2->next == NULL && head2->data == 0))
    {
        printf("Error: Division by zero\n");
        insert_last(headR, tailR, 0);
        return;
    }

    if (head1 == NULL)
    {
        insert_last(headR, tailR, 0);
        return;
    }

    /* Find tail of divisor */
    node *tail2 = head2;
    while (tail2->next != NULL)
        tail2 = tail2->next;

    /* Find tail of dividend */
    node *tail1 = head1;
    while (tail1->next != NULL)
        tail1 = tail1->next;

    node *headAR = NULL;
    node *tailAR = NULL;
    node *temp = head1;
    int q_start = 0;

    while (temp != NULL)
    {
        insert_last(&headAR, &tailAR, temp->data);
        remove_pre_zeros(&headAR);

        if (headAR != NULL)
        {
            tailAR = headAR;
            while (tailAR->next != NULL)
                tailAR = tailAR->next;
        }

        int q = 0;
        while (compare_list(headAR, head2) != OPERAND2) 
        {
            node *headR1 = NULL;
            node *tailR1 = NULL;
            subtraction(tailAR, tail2, &headR1, &tailR1);
            delete_list(&headAR, &tailAR);
            headAR = headR1;
            tailAR = tailR1;
            q++;
        }

        if (q > 0 || q_start)
        {
            insert_last(headR, tailR, q);
            q_start = 1;
        }

        temp = temp->next;
    }

   
    if (*headR == NULL)
        insert_last(headR, tailR, 0);// smaller than divisor

    
    if (headAR != NULL)
        delete_list(&headAR, &tailAR);//free the List by deleting it
}