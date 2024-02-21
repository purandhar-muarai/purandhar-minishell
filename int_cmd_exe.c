#include "main.h"

extern stoped_list *head;

void execute_int_cmd(char *input)
{
    if(strcmp(input, "exit") == 0)
    {
        exit(0);
    }
    else if(strcmp(input, "pwd") == 0)
    {
        printf("%s\n", get_current_dir_name());
    }
    else if(strncmp(input, "cd ",3) == 0)
    {
        chdir(input+3);
    }
    else if(strcmp(input, "jobs") == 0) 
    {
        print_list(head);
    }
    else if(strcmp(input, "fg") == 0)
    {
        if(head != NULL) 
        {
            foreground_process(&head);
        }
        else
        {
            printf("No jobs are present\n");
        }
    }
    else if(strcmp(input, "bg") == 0)
    {
        if(head != NULL)
        {
            background_process(&head);
        }
        else
        {
            printf("No jobs are present\n");
        }
    }
}
