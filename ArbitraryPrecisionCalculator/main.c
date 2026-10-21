#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
    int neg = 0;
    int neg1 = 0, neg2 = 0;

    // Validation
    if (cla_validation(argc, argv) == FAILURE)
    {
        printf("./a.out operand1 operator operand2\n");
        return FAILURE;
    }

    char *op1 = argv[1];
    char *op2 = argv[3];
    if (op1[0] == '-') { neg1 = 1; op1++; }
    if (op2[0] == '-') { neg2 = 1; op2++; }

    // Create 2 lists of operands
    create_list(op1, &head1, &tail1);
    create_list(op2, &head2, &tail2);

    // Remove pre zeros
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    char op = argv[2][0];

    switch (op)
    {
    case '+':
        if (neg1 == neg2)              
        {
            addition(tail1, tail2, &headR, &tailR);
            neg = neg1;
        }
        else if (!neg1 && neg2)         
        {
            int ret = compare_list(head1, head2);
            if (ret == OPERAND1)        
            { 
                subtraction(tail1, tail2, &headR, &tailR); neg = 0; 
            }
            else if (ret == OPERAND2)   
            { 
                subtraction(tail2, tail1, &headR, &tailR); neg = 1; 
            }
            else                        
            { 
                insert_last(&headR, &tailR, 0); 
            }
        }
        else if (neg1 && !neg2) 
        {
            int ret = compare_list(head1, head2);
            if (ret == OPERAND2)        
            { 
                subtraction(tail2, tail1, &headR, &tailR); neg = 0; 
            }
            else if (ret == OPERAND1)   
            { 
                subtraction(tail1, tail2, &headR, &tailR); neg = 1; 
            }
            else                        
            { 
                insert_last(&headR, &tailR, 0); 
            }
        }
        break;

    case '-':
        if (!neg1 && !neg2)           
        {
            int ret = compare_list(head1, head2);
            if (ret == OPERAND1)        
            { 
                subtraction(tail1, tail2, &headR, &tailR); neg = 0; 
            }
            else if (ret == OPERAND2)   
            { 
                subtraction(tail2, tail1, &headR, &tailR); neg = 1; 
            }
            else                        
            { 
                insert_last(&headR, &tailR, 0); 
            }
        }
        else if (neg1 && neg2)       
        {
            int ret = compare_list(head1, head2);
            if (ret == OPERAND2)        
            { 
                subtraction(tail2, tail1, &headR, &tailR); neg = 0; 
            }
            else if (ret == OPERAND1)  
            { 
                subtraction(tail1, tail2, &headR, &tailR); neg = 1; 
            }
            else                        
            { 
                insert_last(&headR, &tailR, 0); 
            }
        }
        else if (!neg1 && neg2)        
        {
            addition(tail1, tail2, &headR, &tailR);
            neg = 0;
        }
        else                            
        {
            addition(tail1, tail2, &headR, &tailR);
            neg = 1;
        }
        break;

    case 'x':
    case 'X':
        multiplication(tail1, tail2, &headR, &tailR);
        neg = (neg1 != neg2) ? 1 : 0; 
        break;

    case '/':
        division(head1, head2, &headR, &tailR);
        neg = (neg1 != neg2) ? 1 : 0;  
        break;

    default:
        printf("Invalid operator\n");
    }

    printf("Result : ");
    if (neg && !(headR != NULL && headR->next == NULL && headR->data == 0))
        printf("-");
    print_list(headR);
    printf("\n");

    return SUCCESS;
}