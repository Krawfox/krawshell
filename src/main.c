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
    "exit"
};

int (*inbuild_func[]) (char **) =
{
    &kraw_cd,
    &kraw_exit,
    &kraw_help
};

int kraw_no_inbuild() {
  return sizeof(inbuild_str) / sizeof(char *);
}


void kraw_loop(void)
{
    char *line;
    char **args;
    int status;
    // This is the important section cuz it init the whole user input thing; imp !!
    do{
        printf(">⩊<.ᐟ ");
        line = kraw_read_line();
        args = kraw_split_line(line);
        status = kraw_execute(args);

        free(line);
        free(args);
    } while (status);

 printf("I am a fool");
}

int main(int argc, char **argv)
{
  // Load config files, if any.
  // Run command loop.
  kraw_loop();
  return EXIT_SUCCESS;
}