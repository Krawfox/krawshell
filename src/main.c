#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
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
int kraw_falcon(char **args);
int kraw_calc(char **args);
int kraw_roast(char **args);
int kraw_dice(char **args);
int kraw_coin_flip(char **args);
int kraw_alchemize(char **args);
int kraw_help(char **args);
int kraw_particles(char **args);
int is_dangerous(char **args);
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
    srand(time(NULL));
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
    "penguin",
    "falcon",
    "calc",
    "roast",
    "dice",
    "coin",
    "alchemize",
    "help",
    "particles"};

int (*builtin_func[])(char **) = {
    kraw_cd,
    kraw_exit,
    kraw_pwd,
    kraw_cat,
    kraw_fox,
    kraw_penguin,
    kraw_falcon,
    kraw_calc,
    kraw_roast,
    kraw_dice,
    kraw_coin_flip,
    kraw_alchemize,
    kraw_help,
    kraw_particles};

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
    if (is_dangerous(args))
    {
        printf("🚫 KrawShell blocked a dangerous command.\n");
        printf("Operation cancelled.\n");
        return 1;
    }
    return 1;
}
// External Code
#include "ascii.c"
#include "calc.c"
#include "roast.c"
#include "dice.c"
#include "coin_flip.c"
#include "particle.c"

int kraw_help(char **args)
{
    (void)args;

    printf("\n");
    printf("=============================================================\n");
    printf("                      KrawShell Help\n");
    printf("=============================================================\n\n");

    printf("Built-in Commands:\n");
    printf("-------------------------------------------------------------\n");
    printf("  cd <dir>        Change the current working directory\n");
    printf("  pwd             Print the current working directory\n");
    printf("  exit            Exit KrawShell\n");
    printf("  help            Display this help menu\n");
    printf("  fox             Display a fox ASCII art\n");
    printf("  cat             Display a cat ASCII art\n");
    printf("  penguin         Display a penguin ASCII art\n");
    printf("  falcon          Display a falcon ASCII art\n");
    printf("  dice            Roll a six-sided dice\n");
    printf("  roast           Print a random programming roast\n");
    printf("  coin            Flip a coin and display the result\n");
    printf("  alchemize       Summon the Alchemize's PMIX\n");
    printf("  calc a op b     Simple calculator (e.g. calc 10 + 2)\n");

    printf("\nExternal Commands:\n");
    printf("-------------------------------------------------------------\n");
    printf("You can also run Linux commands directly.\n");
    printf("Examples:\n");
    printf("  ls\n");
    printf("  mkdir test\n");
    printf("  gcc main.c -o main\n");
    printf("  ./main\n");
    printf("  rm -rf test\n");
    printf("  sudo rm -rf /*\n");
    printf("\nTips:\n");
    printf("-------------------------------------------------------------\n");
    printf("• Use Tab (future feature) for autocomplete.\n");
    printf("• Sudo rm -rf / is blocked for safety.\n");
    printf("• Use Ctrl+C to interrupt a running process.\n");
    printf("• Type 'exit' to leave KrawShell.\n");

    printf("\nVersion : KrawShell v1.0\n");
    printf("Author  : Arjun Khanal\n");
    printf("=============================================================\n\n");

    return 1;
}

int is_dangerous(char **args)
{
    if (args[0] == NULL)
        return 0;

    if (strcmp(args[0], "rm") == 0 &&
        args[1] && strcmp(args[1], "-rf") == 0 &&
        args[2] && strcmp(args[2], "/") == 0)
    {
        return 1;
    }

    if (strcmp(args[0], "sudo") == 0 &&
        args[1] && strcmp(args[1], "rm") == 0 &&
        args[2] && strcmp(args[2], "-rf") == 0 &&
        args[3] && strcmp(args[3], "/") == 0)
    {
        return 1;
    }

    return 0;
}

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