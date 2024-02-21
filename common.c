#include "main.h"

extern int pid, exit_status;

stoped_list *head = NULL;

int check_command_type(char *input)
{
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
        "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
        "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","jobs","fg","bg", NULL};

    char *array = malloc(strlen(input) +1);
    strcpy(array,input);

    char *cmd = strtok(array, " ");

    for(int i = 0; builtins[i] != NULL; i++)
    {
        if(strcmp(cmd, builtins[i]) == 0)
            return INT_CMD;
    }

    return EXT_CMD;
}

void get_cmd(char *input, char *cmd[])
{
    char *token = strtok(input, " ");
    int i = 0;

    while(token != NULL)
    {
        cmd[i] = malloc(strlen(token) + 1);
        strcpy(cmd[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    cmd[i] = NULL;
}

void signal_handler(int signum)
{
    switch(signum)
    {
        case SIGINT:
            if(pid)
            {
                kill(pid, SIGINT);
                exit_status = 128 + SIGINT;
            }
            break;
        case SIGTSTP:
            if(pid)
            {
                // adding to linked list
                add_list(pid, &head);
                printf("[%d]  stopped\n", pid);
                kill(pid, SIGTSTP);
                exit_status = 128 + SIGTSTP;
            }
            break;
    }
    printf("\n");
}
