#ifndef MAIN_H
#define MAIN_H

#define  _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <error.h>


#define INT_CMD   0
#define EXT_CMD   1

typedef struct stoped_list
{
    int pid;
    struct stoped_list *next;
}stoped_list;

int check_command_type(char *);
int execute_ext_cmd(char *);
void execute_int_cmd(char *);
void get_cmd(char *input, char *cmd[]);
void signal_handler(int );
void print_list(stoped_list *head);
void add_list(int pid, stoped_list **head);
void foreground_process(stoped_list **head);
void background_process(stoped_list **head);

#endif
