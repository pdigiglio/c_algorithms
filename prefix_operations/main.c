#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float operand(const char* s, float prev)
{
    float value = prev;
    if (0 != strcasecmp(s, "PREV"))
    {
        value = atof(s);
    }

    return value;
}

float do_operation(char optor, float lhs, float rhs)
{
    switch(optor)
    {
        case '+':
            return lhs + rhs;

        case '-':
            return lhs - rhs;

        case '*':
            return lhs * rhs;

        case '/':
            return lhs / rhs;

        default:
            printf("Invalid operator '%c'", optor);
            return 0;
    }
}

#define OPERAND_STRLEN 6
#define QUIT_OPERATOR  '!'

int main()
{
    char leftOperand[OPERAND_STRLEN] = {};
    char rightOperand[OPERAND_STRLEN] = {};

    char optor = '\0';
    float prev = 0;

    while (1)
    {
        printf("> (prev: %f) ", prev);
        scanf(" %c", &optor);
        if (QUIT_OPERATOR == optor)
        {
            puts("Exiting");
            break;
        }

        scanf("%s %s", leftOperand, rightOperand);
        float lhs = operand(leftOperand, prev);
        float rhs = operand(rightOperand, prev);
        prev = do_operation(optor, lhs, rhs);
        printf(" %f\n", prev);
    }

    return 0;
}
