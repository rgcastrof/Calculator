#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


// structs
typedef struct
{
    double number_one;
    double number_two;
    char operator;
    double (*calc)(double, double, const char);
} Calculator;


// function declarations
double calculate(double n1, double n2, const char op);
Calculator createCalc(double n1, double n2, const char op);
void help(char *arg);


//function implementations
double
calculate(double n1, double n2, const char op)
{
    double result = 0;

    switch (op)
    {
        case '+':
            result = n1 + n2;
            break;
        case '-':
            result = n1 - n2;
            break;
        case '*':
            result = n1 * n2;
            break;
        case '/':
            if (n2 == 0) {
                printf("Error: division by zero.\n");
                exit(EXIT_FAILURE);
            }
            result = n1 / n2;
            break;
        default:
            fprintf(stderr, "Error: invalid operator '%c'.\n", op);
            exit(EXIT_FAILURE);
    }
    return result;
}

Calculator
createCalc(double n1, double n2, const char op)
{
    Calculator calculator;

    calculator.number_one = n1;
    calculator.number_two = n2;
    calculator.operator = op;
    calculator.calc = calculate;

    return calculator;
}

void
help(char *arg)
{
    printf("Options:\n%s [number one] [operator] [number two] to calculate a operation between two numbers.\n", arg);
    printf("%s pow [base] [expoent] to calculate the power of a number.\n", arg);
    printf("%s sqrt [number] to calculate the square root of a number.\n", arg);
}

int
main(int argc, char *argv[])
{
    if (argv[1] != NULL && strcmp(argv[1], "--help") == 0)
    {
        help(argv[0]);
        return EXIT_SUCCESS;
    }

    else if (argv[1] != NULL && strcmp(argv[1], "sqrt") == 0)
    {
        printf("sqrt(%.0lf) = %lf\n",strtod(argv[2], NULL), sqrt(strtod(argv[2], NULL)));
        return EXIT_SUCCESS;
    }
    else if (argv[1] != NULL && strcmp(argv[1], "pow") == 0)
    {
        double base = strtod(argv[2], NULL);
        double expoent = strtod(argv[3], NULL);

        printf("pow(%.0lf, %.0lf) = %.2lf\n", base, expoent, pow(base, expoent));
        return EXIT_SUCCESS;
    }
    else if (argc < 4)
    {
        fprintf(stderr, "Usage: %s [number one] [operator] [number two]\n", argv[0]);
        fprintf(stderr, "\nType %s --help to see a list of options.\n", argv[0]);
        return EXIT_FAILURE;
    }

    Calculator calculator = createCalc(strtod(argv[1], NULL), strtod(argv[3], NULL), *argv[2]);
    double result = calculator.calc(calculator.number_one, calculator.number_two, calculator.operator);

    printf("%s %s %s = %.2lf\n", argv[1], argv[2], argv[3], result);
    return EXIT_SUCCESS;
}
