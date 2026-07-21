int kraw_calc(char **args)
{
    (void)args;
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Usage: calc <num1> <operator> <num2>\n");
        return 1;
    }
    double num1 = atof(args[1]);
    double num2 = atof(args[3]);
    char op = args[2][0];

    switch (op)
    {
    case '+':
        printf("Sum Of Numbers : %g\n", num1 + num2);
        break;
    case '-':
        printf("Difference Of Numbers : %g\n", num1 - num2);
        break;
    case '*':
        printf("Product Of Numbers : %g\n", num1 * num2);
        break;
    case '/':
        if (num2 == 0)
        {
            printf("Cannot Divide By Zero \n");
        }
        else
        {
            printf("Division Between Numbers : %g\n", num1 / num2);
        }
        break;

    default:
        printf("Unknown operator.\n");
        break;
    }
    return 1;
}