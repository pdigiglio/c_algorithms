#include <stdio.h>

#define MAX_DEGREE 10

void advance_stdin()
{
    while (getchar() != '\n') continue;
}

int scanf_single_int(int* parsedValue)
{
    if (0 == scanf(" %d", parsedValue))
    {
        puts("Invalid integer");
        advance_stdin();
        return 0;
    }

    return 1;
}

int scanf_single_float(float* parsedValue)
{
    if (0 == scanf(" %f", parsedValue))
    {
        puts("Invalid float");
        advance_stdin();
        return 0;
    }

    return 1;
}

int read_degree()
{
    int degree = -1;
    while (1)
    {
        printf("Enter degree (0 <= degree <= %d): ", MAX_DEGREE);

        if(0 == scanf_single_int(&degree))
            continue;

        if (degree < 0 || degree > MAX_DEGREE)
        {
            puts("Out of range");
            advance_stdin();
            continue;
        }

        break;
    }

    return degree;
}

int read_coefficients(int degree, float* coefficients)
{
    int d = 0;
    while (d <= degree)
    {
        printf("Enter coefficient for degree %d: ", d);
        if (0 == scanf_single_float(coefficients + d))
        {
            continue;
        }

        ++d;
    }

    return d;
}

void read_integration_interval(int* integrationInterval)
{
    while (1)
    {
        printf("Enter integration-interval lower bound (int): ");
        if (0 == scanf_single_int(integrationInterval))
            continue;

        break;
    }

    while (1)
    {
        printf("Enter integration-interval upper bound (int): ");
        if (0 == scanf_single_int(integrationInterval + 1))
        {
            continue;
        }

        if (integrationInterval[0] > integrationInterval[1])
        {
            printf("Lower bound (%d) greater than upper bound (%d)\n",
                    integrationInterval[0], integrationInterval[1]);
            advance_stdin();
            continue;
        }

        break;
    }
}

int read_subintervals()
{
    int subintervals = 0;
    while (1)
    {
        printf("Enter number of subintervals (> 0): ");
        if (0 == scanf_single_int(&subintervals))
            continue;

        if (subintervals <= 0)
        {
            puts("Invalid number of subintervals");
            advance_stdin();
            continue;
        }
        
        break;
    }

    return subintervals;
}

float eval_horner(const float *coefficients, float x)
{
    const float* cn = coefficients + MAX_DEGREE;
    float c = x * (*cn--);
    c += *cn;

    while (cn != coefficients - 1)
    {
        c *= x;
        c += (*cn--);
    }

    return c;
}

int main()
{
    int degree = read_degree();
    printf("> degree: %d\n", degree);

    float coefficients[MAX_DEGREE + 1] = {};
    read_coefficients(degree, coefficients);

    printf("> ");
    for (int d = 0; d <= degree; ++d)
    {
        printf("%+f[x^%d] ", coefficients[d], d);
    }
    puts("");

    int integrationInterval[2] = {};
    read_integration_interval(integrationInterval);
    printf("> integration interval: [%d, %d)\n", integrationInterval[0], integrationInterval[1]);

    int subintervals = read_subintervals();
    printf("> subintervals: %d\n", subintervals);

    float step = (integrationInterval[1] - integrationInterval[0]) / (float)subintervals;
    float integral = 0;
    for (float x = integrationInterval[0] + 0.5 * step; x < integrationInterval[1]; x += step)
    {
        integral += step * eval_horner(coefficients, x);
    }

    printf("> Integral: %f\n", integral);

    return 0;
}
