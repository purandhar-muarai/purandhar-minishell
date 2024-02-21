#include "main.h"

extern int exit_status;
void foreground_process(stoped_list **head)
{

    stoped_list *temp = *head, *prev = NULL;
    if(temp -> next == NULL)
    {
        *head = NULL;
    }
    else
    {
        while(temp -> next != NULL)
        {
            prev = temp;
            temp = temp-> next;
        }
        prev -> next = NULL;
    }
    // Bring the process to the foreground
    printf("%d\n", temp->pid);

    tcsetpgrp(1,getpgid(temp->pid));

    if(kill(temp -> pid, SIGCONT) < 0)
    {
        perror("kill");
    }
    int status;
    waitpid(temp->pid,&status,WUNTRACED);
    exit_status = WIFEXITED(status);
   // printf("\n");
}

void background_process(stoped_list **head)
{

    stoped_list *temp = *head, *prev = NULL;
    if(temp -> next == NULL)
    {
        *head = NULL;
    }
    else
    {
        while(temp -> next != NULL)
        {
            prev = temp;
            temp = temp-> next;
        }
        prev -> next = NULL;
    }
    printf("%d\n", temp->pid);
    if(kill(temp -> pid, SIGCONT) < 0)
    {
        perror("kill");
    }
    free(temp);
    printf("process started in background\n");
}

