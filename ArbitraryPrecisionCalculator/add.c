#include "apc.h"
/*addition function declaration*/
void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;
    int sum = 0 ,res = 0;
    while(tail1 != NULL || tail2 != NULL)
    {
        sum = carry;

        if(tail1 != NULL)
        {
            sum = sum + tail1->data;
            tail1 = tail1->prev;
        }
        if(tail2 != NULL)
        {
            sum = sum + tail2->data;
            tail2 = tail2->prev;
        }
        res = sum % 10;
        carry = sum / 10;
       insert_first(headR,tailR, res);
    }
    if(carry == 1)
    {
        insert_first(headR,tailR, carry);
    }
}