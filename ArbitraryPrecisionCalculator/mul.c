#include "apc.h"
/*multiplication function declaration*/
void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *headAR = NULL;
    node *tailAR = NULL;
    node *temp2 = tail2;
    int count = 0;

    while (temp2 != NULL)
    {
        node *temp1 = tail1;
        *headR = NULL;
        *tailR = NULL;
        int carry = 0;

        for (int i = 0; i < count; i++)
        {
            insert_first(headR, tailR, 0);
        }

        while (temp1 != NULL)
        {
            int result = temp1->data * temp2->data + carry;
            carry = result / 10;
            result = result % 10;
            insert_first(headR, tailR, result);
            temp1 = temp1->prev;
        }

        if (carry)
        {
            insert_first(headR, tailR, carry);
        }

        if (headAR == NULL)
        {
            headAR = *headR;
            tailAR = *tailR;
        }
        else
        {
            node *oldHeadAR = headAR;
            node *oldTailAR = tailAR;
            node *newHead = NULL;      
            node *newTail = NULL;      

            addition(oldTailAR, *tailR, &newHead, &newTail);

            delete_list(headR, tailR);        
            delete_list(&oldHeadAR, &oldTailAR); 

            headAR = newHead;   
            tailAR = newTail;
        }

        count++;
        temp2 = temp2->prev;
    }

    *headR = headAR;
    *tailR = tailAR;
}