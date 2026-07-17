#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Inbuild functions arguments
int kraw_cd(char **args);
int kraw_help(char **args);
int kraw_exit(char **args);

// These will be the inbuild functions (Need to add more functions during next updates)
char *inbuild_str[] = {
    "cd"
    "help"
    "exit"};

int (*inbuild_func[])(char **) =
    {
        &kraw_cd,
        &kraw_exit,
        &kraw_help};

int kraw_no_inbuild()
{
    return sizeof(inbuild_str) / sizeof(char *);
}

void kraw_loop(void)
{
    char *line;
    char **args;
    int status;
    // This is the important section cuz it init the whole user input thing; imp !!
    do
    {
        printf(">⩊<.ᐟ ");
        line = kraw_read_line();
        args = kraw_split_line(line);
        status = kraw_execute(args);

        free(line);
        free(args);
    } while (status);

    printf("I am a fool");
}

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
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
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

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize)
        {
            bufsize += KRAW_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "kraw: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define KRAW_TOK_BUFSIZE 64
#define KRAW_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line)
{
    int bufsize = KRAW_TOK_BUFSIZE, position = 0;
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
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += KRAW_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "kraw: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, KRAW_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int main(int argc, char **argv)
{
    // Load config files, if any.
    // Run command loop.
    kraw_loop();
    return EXIT_SUCCESS;
}