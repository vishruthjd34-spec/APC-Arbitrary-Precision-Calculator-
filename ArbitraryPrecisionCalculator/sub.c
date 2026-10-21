#include "apc.h"
/*subtraction function declaration*/
void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow_flag = 0;
    while(tail1 != NULL || tail2 != NULL)
    {
        int dig1 = 0;
        int dig2 = 0;
        if(tail1 != NULL)
        {
            dig1 = tail1->data;
            tail1 = tail1->prev;
        }
        if(tail2 != NULL)
        {
            dig2 = tail2->data;
            tail2 = tail2->prev;
        }
        dig1 = dig1 - borrow_flag;
        if(dig1 < dig2)
        {
            dig1 = dig1 + 10;
            borrow_flag = 1;
        }
        else
        {
            borrow_flag = 0;
        }
        insert_first(headR,tailR,dig1- dig2);
    }
    remove_pre_zeros(headR);
}