/*
    Project name : Minishell
    Authur : Purandhar Murarisetty
 */



#include "main.h"


int main()
{
    char prompt[20] = "minishell$ ", input[50];
    int ret, exit_val;
    //char *ptr;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = signal_handler;
    //act.sa_flags = SA_NOCLDWAIT | SIGCHLD;
   //fc.sa_handler = signal_handler; 

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);
    //sigaction(SIGCHLD, &act, NULL);
    while(1)
    {
        printf("%s",prompt);
        fgets(input, 50, stdin);

        input[strlen(input) - 1] = '\0'; // making \n to null
        //ptr = strchr(input, '\n');

        if(*input == '\0') 
            continue;
        else if(strncmp(input, "PS1=", 4) == 0)
        {
            // change prompt name
            if(input[4] != ' ')
            {
                strcpy(prompt, input+4);
                strcat(prompt, "$ \0");

            }
            else
                printf("Command not found\n");
        }

        else if(strcmp(input, "echo $$") == 0)
        {
            //prints pid of the shell
            printf("%d\n",getpid());
        }
        else if(strcmp(input, "echo $SHELL") == 0)
        {
            // prints the path of the shell
            printf("%s/%s\n", get_current_dir_name(),prompt);
        }
        else if(strcmp(input, "echo $?") == 0)
        {
            printf("%d\n",exit_val);
        }
        else if((ret = check_command_type(input)) ==  EXT_CMD)
        {
            //printf("Ext cmd");
            exit_val = execute_ext_cmd(input);
        }
        else if(ret == INT_CMD)
        {
            //printf("Internal cmd");
            execute_int_cmd(input);
        }

        else
            printf("Command not found\n");
    }
}
