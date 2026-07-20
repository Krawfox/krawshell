int kraw_roast(char **args)
{
    (void)args;
    const char *roasts[] = {
        "You're the reason the 'Undo' button exists.",
        "404: Intelligence Not Found.",
        "Your code compiles... by accident.",
        "Even the compiler is judging you.",
        "Segmentation fault? More like programmer fault.",
        "Your variables have better names than your life choices.",
        "Git saw your commits and asked for a rollback.",
        "Your CPU called in sick after running your code.",
        "The garbage collector refused to collect this mess.",
        "You put the 'bug' in debugging."};
        int n = sizeof(roasts) / sizeof(roasts[0]);
        printf ("%s\n", roasts[rand()%n]);
        return 1;
}