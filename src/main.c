#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Initializing Every Single Function That will be on the Shelly

// Build In Commands :Kraw's 
int kraw_cd(char **args);
int kraw_ls(char **args);
int kraw_exit(char **args);

// Shell Functions ( Custom commands )
void kraw_loop(void);
char *kraw_read_line(void);
char **kraw_split_line(char *line);
int kraw_launch(char **args);
int kraw_execute(char **args);
int kraw_num_builtins(void);


