#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Initializing Every Single Function That will be on the Shelly

// : function prototype
// Build In Commands
int kraw_cd(char **args);
int kraw_help(char **args);
int kraw_exit(char **args);

// Shell Functions
void kraw_loop(void);
char *kraw_read_line(void);
char **kraw_split_line(char *line);
int kraw_launch(char **args);
int kraw_execute(char **args);
int kraw_num_builtins(void);

// main function that works
int main(void)
{
    kraw_loop();
    return EXIT_SUCCESS;
}

// Build In Commands

char *builtin_str[] =
    {
        "cd",
        "help",
        "exit"};

int (*builtin_func[])(char **) = {
    kraw_cd,
    kraw_help,
    kraw_exit};

int kraw_num_builtins(void)
{
    return sizeof(builtin_str) / sizeof(char *);
}

// SHell Loop Main Input section

void kraw_loop(void)
{
    char *line;
    char **args;
    char status;
    do
    {
        printf("Kraw: ");
        fflush(stdout);

        line = kraw_read_line();
        args = kraw_split_line(line);

        status = kraw_execute(args);

        free(args);
        free(line);

    } while (status);
}

// Next part Is Reading the stuff

#define KRAW_RL_BUFSIZE 1024

char *kraw_read_line(void)
{
    int bufsize = KRAW_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char)* bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "kraw: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* code */
         c = getchar();

        if (c == EOF || c = '\n')
        {
            buffer[position] = '\0';
        }
        else 
        {
            buffer[position] =c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += KRAW_RL_BUFSIZE;
            buffer = realloc(buffer, sizeof(char) *bufsize);

            if(!buffer)
            {
                fprintf(stderr, "kraw: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    
}