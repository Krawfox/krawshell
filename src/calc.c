int kraw_calc(char **args)
{
    (void)args;
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Usage: calc <num1> <operator> <num2>\n");
        return 1;
    }
    int num1 = atoi(args[1]);
    int num2 = atoi(args[3]);
    int op = args[2][0];

    switch (op)
    {
    case '+':
        printf("%d\n", num1 + num2);
        break;
    case '-':
        printf("%d\n", num1 - num2);
        break;
    case '*':
        printf("%d\n", num1 * num2);
        break;
    case '/':
        if (num2 == 0)
        {
            printf("Cannot Divide By Zero \n");
        }
        else
        {
            printf("%d\n", num1 / num2);
        }
        break;

    default:
        printf("Unknown operator.\n");
        break;
    }
    return 1;
}