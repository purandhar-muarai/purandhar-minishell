#include "main.h"

void add_list(int pid, stoped_list **head)
{
    stoped_list *new = malloc(sizeof(stoped_list));
    new -> pid = pid;
    new -> next = NULL;
    if(*head == NULL)
    {
        *head = new;
    }
    else 
    {
        stoped_list *temp = *head;

       while(temp -> next)
       {
           temp = temp -> next;
       } 
       temp -> next = new;
    }
}

void print_list(stoped_list *head)
{
    stoped_list *temp = head;
    while(temp)
    {
        printf("%d\n", temp -> pid);
        temp = temp -> next;
    }
}
