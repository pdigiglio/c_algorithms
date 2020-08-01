#include <stdio.h>

void column_multiply(
    const unsigned char* lhs, const unsigned char* rhs, unsigned size,
    unsigned char* result)
{
    if (0 == size)
        return;

    unsigned resultShift = size;
    unsigned l = size;
    do
    {
        --l;
        unsigned char remainder = 0;
        unsigned r = size;
        do
        {
            --r;
            unsigned char sum = remainder + result[resultShift + r] +
lhs[l] * rhs[r];
            result[resultShift + r] = sum % 10;
            remainder = sum / 10;
        } while (r);

        result[--resultShift] = remainder;
    } while (l);
}

void reverse_vector(unsigned char* v, unsigned size)
{
    unsigned char i = 0;
    --size;

    while (i < size)
    {
        unsigned char tmp = v[i];
        v[i] = v[size];
        v[size] = tmp;

        ++i;
        --size;
    }
}

void print_number(const unsigned char* number, unsigned size)
{
    const unsigned char* const last = number + size;
    for (; number != last; ++number)
    {
        printf("%d",  *number);
    }

    puts("");
}

int main()
{
    unsigned char lhs[] = { 0, 3, 2 };
    print_number(lhs, 3);

    unsigned char rhs[] = { 2, 4, 3 };
    print_number(rhs, 3);

    unsigned char result[6] = {};

    column_multiply(lhs, rhs, sizeof(lhs) / sizeof(lhs[0]), result);
    print_number(result, sizeof(result) / sizeof(result[0]));

    return 0;
}
