int kraw_coin_flip(char **args)
{
    (void)args;
    const char *coin[] = {"Head","Tail"};
    int n = sizeof(coin)/sizeof(coin[0]);
    printf ("%s\n",coin[rand()% n]);
    return 1;
}