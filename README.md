# Krawshell

 A lightweight Linux shell written in C, built from scratch as a learning project.


### Shell

- Execute external Linux commands
- Built-in command support
- Process creation using `fork()`
- Command execution using `execvp()`
- Process waiting with `waitpid()`
- Dynamic input parsing
- Tokenization using `strtok()`

### Built-in Commands

| Command | Description |
|---------|-------------|
| `help` | Show help menu |
| `cd <dir>` | Change directory |
| `pwd` | Print working directory |
| `exit` | Exit KrawShell |
| `fox` | Display a fox ASCII art |
| `cat` | Display a cat ASCII art |
| `dice` | Roll a random six-sided dice |
| `roast` | Print a random roast |
| `alchemize` | Display the Alchemize Pmix |
| `calc` | Perform basic arithmetic *(planned/improving)* |

``` There are Multiple Commands make sure to run help to get the list inside the shell ```

### Requirements

- GCC
- Linux / WSL

# ALMOST ALL LINUX DISTRO IS SUPPORTED BUT Mac OS not Tested ( May not work probably)

# Setup 

### Clone

```bash
git clone https://github.com/Krawfox/krawshell.git
cd krawshell/src
```

### Compile

```bash
 gcc main.c -o kraw
```

### Run

```bash
./kraw
```

# THEME

The project belongs to the no internet theme since it is a terminal based shell which don't require internet to work , just get the compiled file and run using termianl just need ./kraw

# Inspiration

Since I need to learn C language so I think why not do a project based learning so I searched up the google and there was a good resource that told to build your own shell so I got the idea from that so I am building this shell for my computer and Ig I might add some automations too.

# Screenshots 
<img width="1383" height="791" alt="Screenshot 2026-07-22 173438" src="https://github.com/user-attachments/assets/2bd6be09-d0fe-47f1-844f-5ceec62bee4a" />
<img width="1388" height="797" alt="Screenshot 2026-07-22 173458" src="https://github.com/user-attachments/assets/72cdae99-810a-4cbb-a526-5257e0bf7eb3" />



## Author

**Arjun Khanal**

Made with ☕, C, and a lot of debugging.
