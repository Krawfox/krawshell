int kraw_dice(char **args)
{
    (void)args;
    const char *dice[] = {"1", "2", "3", "4", "5", "6"};
    int n = sizeof(dice) / sizeof(dice[0]);
    printf("%s\n", dice[rand() % n]);
    return 1;
}