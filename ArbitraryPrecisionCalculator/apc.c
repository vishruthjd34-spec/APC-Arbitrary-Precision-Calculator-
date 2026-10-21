#include "apc.h"
/*for input validation*/
int cla_validation(int argc, char *argv[])
{
    if (argc != 4)
    {
        return FAILURE;
    }
    return SUCCESS;
}
/*To create a new linked list*/
void create_list(char *opr, node **head, node **tail)
{
    int i = 0;
    while(opr[i] != '\0')
    {
        insert_last(head,tail,opr[i]-'0');
        i++;
    }

}
/*Function to remove the zeros at the starting */
void remove_pre_zeros(node **head)
{
    node *temp;
    while(*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        temp = *head;
        *head = temp->next;
        (*head)->prev =  NULL;
        free(temp);
    }
}
/*Function to insert a node at last of the function*/
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->next = NULL;

    if (*head == NULL)
    {
        new->prev = NULL; 
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}
/*Function to insrt a node at the beginning of the linked list*/
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    /*Check for memory allocation*/
    if(new == NULL)
        return FAILURE;
    new->prev = NULL;
    new->next = NULL;
    new->data = data;
    /*If list is empty*/
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    /*Insert before the current head*/
    new->next = *head;
    (*head)->prev = new;
    *head = new;
    return SUCCESS;
}
/*Function to delete the list and free the memory*/
int delete_list(node **head, node **tail)
{
    node *temp;

    while(*head)
    {
        temp = *head;
        *head = temp->next;
        free(temp);
    }

    *tail = NULL;

    return SUCCESS;
}
    
/*Function to display the linked list*/
void print_list(node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    
}
/*Function to comapare operands in linked lists*/
int compare_list(node *head1, node *head2)
{
   int len1 = list_len(head1);
   int len2 = list_len(head2);
   /*compare based on the number of digits*/
   if(len1 > len2)
        return OPERAND1;
   else if(len1 < len2)
       return OPERAND2;
   else
   {
    node *temp1 = head1;
    node *temp2 = head2;

    while(temp1 != NULL && temp2 != NULL)//compare digit by digit till lengths are equal
    {
        if(temp1->data > temp2->data)
        {
            return OPERAND1;
        }
        else if(temp1->data < temp2->data)
        {
            return OPERAND2;
        }
        
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return SAME; // for both the operands are equal
   }

}
int list_len(node *head) //  function to calculate the number of nodes in the linked list
{
    int count = 0;

    while(head != NULL)
    {
        head = head->next;
        count++;
    }
    return count;
}