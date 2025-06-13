#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

// calculator arguments
typedef struct Arg {
    char** args; // Array with the arguments readed
    int size; // Size of arguments
    double* nums; // Array with the numbers readed
    char** ops; // Array with the opereators readed
} Arg;

// Returns a pointer for the arguments struct
Arg*
create_calc() {
    Arg* arg = malloc(sizeof(Arg));
    arg->args = NULL;
    arg->size = 0;
    arg->nums = NULL;
    arg->ops = NULL;
    return arg;
}

// Convert the numbers in the buffer to a array of double
double*
append
(char** str, int total_tokens, int* nums_size) {
    double* arr = malloc(total_tokens * sizeof(double));
    int j = 0;
    for (int i = 0; i < total_tokens; i++) {
        if (strcmp(str[i], "+") != 0 &&
            strcmp(str[i], "-") != 0 &&
            strcmp(str[i], "*") != 0 &&
            strcmp(str[i], "/") != 0) {
            arr[j++] = atof(str[i]);
        }
    }
    *nums_size = j;
    return arr;
}

// Returns an array with only the operators
char**
append_ops
(char** str, int total_tokens, int* ops_size) {
    char** arr = malloc(total_tokens * sizeof(char*));
    int j = 0;
    for (int i = 0; i < total_tokens; i++) {
    
        if (strcmp(str[i], "+") == 0 ||
            strcmp(str[i], "-") == 0 ||
            strcmp(str[i], "*") == 0 ||
            strcmp(str[i], "/") == 0) {
            arr[j++] = str[i];
        }
    }
    *ops_size = j;
    return arr;
}

// Returns the result of the operation
double
evaluate
(double* nums, char** ops, int ops_size, int nums_size) {
    // first loop to evaluate operations with precedence
    for (int i = 0; i < ops_size;) {
        if (strcmp(ops[i], "*") == 0 || (strcmp(ops[i], "/") == 0)) {
            if (strcmp(ops[i], "*") == 0) {
                nums[i] *= nums[i+1];
            } else {
                if (nums[i + 1] == 0) {
                    fprintf(stderr, "error: division by zero\n");
                    return 0.0;
                }
                nums[i] /= nums[i+1];
            }

            for (int j = i + 1; j < nums_size - 1; j++) {
                nums[j] = nums[j+1];
            }
            nums_size--;
            for (int j = i; j < ops_size - 1; j++) {
                ops[j] = ops[j+1];
            }
            ops_size--;
        } else {
            i++;
        }
    }
    double result = nums[0];
    for (int i = 0; i < ops_size; i++) {
        if (strcmp(ops[i], "+") == 0) {
            result += nums[i+1];
        } else if (strcmp(ops[i], "-") == 0) {
            result -= nums[i+1];
        }
    }

    return result;
}

int
main
(int argc, char *argv[])
{
    Arg* arg = create_calc();
    int nums_size;
    int ops_size;

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            printf("usage: %s \n", argv[0]);
            printf("The program will start in interactive mode if no expression is specified\n");
            return EXIT_SUCCESS;
        }
        arg->args = malloc((argc - 1) * sizeof(char*));
        for (int i = 1; i < argc; i++) {
            arg->args[i - 1] = argv[i];
        }
        arg->nums = append(arg->args, argc-1, &nums_size);
        arg->ops = append_ops(arg->args, argc-2, &ops_size);
        printf("  %.2f\n", evaluate(arg->nums, arg->ops, ops_size, nums_size));
        free(arg->args);
        free(arg->nums);
        free(arg->ops);
        return EXIT_SUCCESS;
    }

    char buffer[100];

    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
        printf("%s ", buffer);
        arg->args = strsplt(buffer);
        arg->size = spltsize(arg->args);
        if (!is_digit(arg->args[0])) {
            fprintf(stderr, "fail: invalid input\ntry with spaces\n");
            freesplt(arg->args, arg->size);
            continue;
        }

        arg->nums = append(arg->args, arg->size, &nums_size);
        arg->ops = append_ops(arg->args, arg->size, &ops_size);
        printf("= %.2f\n", evaluate(arg->nums, arg->ops, ops_size, nums_size));

        free(arg->nums);
        free(arg->ops);
        freesplt(arg->args, arg->size);
    }
    return 0;
}
