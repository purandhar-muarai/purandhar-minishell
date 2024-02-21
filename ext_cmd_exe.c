#include "main.h"

int pid, exit_status;
void sigchild_handler(int signo)
{
    int status;
    waitpid(-1, &status, WNOHANG);
}

int execute_ext_cmd(char *input)
{
    if(strlen(input) == 1) { return 0;}
    pid = fork();
    int ret;

    if(pid == 0)
    {
        //child process
        char *cmd[10] = {NULL};

        get_cmd(input, cmd);

        execvp(cmd[0], cmd);

        printf("%s: in child command not found\n",cmd[0]);
        exit(errno);
    }
    else
    {
        
        struct sigaction sig;
        memset(&sig, 0, sizeof(sig));
        sig.sa_handler = sigchild_handler;
        sigaction(SIGCHLD,&sig,NULL);
        
        ret = waitpid(pid, &exit_status, WUNTRACED);
        if(WIFEXITED(exit_status))
        {
            printf("The child %d terminated normally with code %d\n", ret, WEXITSTATUS(exit_status));
            return exit_status;
        }
        else if(WIFSIGNALED(exit_status))
        {
            int ret = WTERMSIG(exit_status);
            if(ret == 2)
                printf("The child %d terminated by reciveing signal %d\n", pid, WTERMSIG(exit_status));
            else if(ret == 20)
                printf("The child %d stopped by reciveing signal %d\n", pid, WTERMSIG(exit_status));
        }
        pid = 0;
        exit_status = 0;
    }
}

