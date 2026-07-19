#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// #include "ascii.h"

// Initializing Every Single Function That will be on the Shelly

// : function prototype
// Build In Commands
int kraw_cd(char **args);
// int kraw_help(char **args);
int kraw_exit(char **args);
int kraw_pwd(char **args);
int kraw_fox(char **args);
int kraw_cat(char **args);
int kraw_penguin(char **args);

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


char *builtin_str[] = {
    "cd",
    "exit",
    "pwd",
    "cat",
    "fox",
    "penguin"
};

int (*builtin_func[])(char **) = {
    kraw_cd,
    kraw_exit,
    kraw_pwd,
    kraw_cat,
    kraw_fox,
    kraw_penguin
};

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
    char *buffer = malloc(sizeof(char) * bufsize);
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

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += KRAW_RL_BUFSIZE;
            buffer = realloc(buffer, sizeof(char) * bufsize);

            if (!buffer)
            {
                fprintf(stderr, "kraw: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Let's split some lines

#define KRAW_TOK_BUFSIZE 64
#define KRAW_TOK_DELIM " \t\r\n\a"

char **kraw_split_line(char *line)
{
    int bufsize = KRAW_TOK_BUFSIZE;
    int position = 0;

    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "kraw: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, KRAW_TOK_DELIM);

    while (token != NULL)
    {
        /* code */
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += KRAW_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "kraw: allocation error \n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, KRAW_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

// THIS IS THE FEATURES YOU WILL BE USING

// THis thing will change the directories

int kraw_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "kraw: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("kraw");
        }
    }
    return 1;
}

int kraw_pwd(char **args)
{
    (void)args;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("kraw");
    }

    return 1;
}
// exit the terminal

int kraw_exit(char **args)
{
    (void)args;
    return 0;
}

// Launch Apps

int kraw_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("kraw");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("kraw");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

#include "ascii.c"

int kraw_execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }
    for (int i = 0; i < kraw_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return builtin_func[i](args);
        }
    }
    return kraw_launch(args);
}