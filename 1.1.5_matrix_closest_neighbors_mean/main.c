#include <assert.h>
#include <stdio.h>

#define MAX_MAT_ROWS 5
#define MAX_MAT_COLS 5

float evaluate_nn_mean(
    const int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS],
    unsigned row, unsigned rows,
    unsigned col, unsigned cols)
{
    //printf("r=%u, c=%u\n", row, col);
    const unsigned rowStart = row - (row > 0);
    const unsigned rowEnd   = row + (row <= rows - 2) + (row <= rows - 1);
    //printf("r in [%u, %u)\n", rowStart, rowEnd);

    const unsigned colStart = col - (col > 0);
    const unsigned colEnd   = col + (col <= cols - 2) + (col <= cols - 1);
    //printf("c in [%u, %u)\n", colStart, colEnd);

    int sum = -inputMatrix[row][col];
    int count = -1;

    for (unsigned r = rowStart; r < rowEnd; ++r)
    {
        for (unsigned c = colStart; c < colEnd; ++c)
        {
            sum += inputMatrix[r][c];
            ++count;
            //printf("i[%u][%u]=%d\n", r, c, inputMatrix[r][c]);
        }
    }

    //printf("sum=%d\n", sum);

    return sum / (float)count;
}

void evaluate_nn_means(
    const int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS],
    unsigned rows,
    unsigned cols,
    float outMatrix[MAX_MAT_ROWS][MAX_MAT_COLS])
{
    for (unsigned r = 0; r < rows; ++r)
    {
        for (unsigned c = 0; c < cols; ++c)
        {
            outMatrix[r][c] = evaluate_nn_mean(inputMatrix, r, rows, c, cols);
        }
    }
}

int main()
{
    unsigned rows = 3;
    unsigned cols = 4;

    int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS] =
    {
         1,  2,  3,  4, 0,
         5,  6,  7,  8, 0,
         9, 10, 11, 12, 0,
         0,  0,  0,  0, 0,
         0,  0,  0,  0, 0
    };

    float meanMatrix[MAX_MAT_ROWS][MAX_MAT_COLS] = {};
    evaluate_nn_means(inputMatrix, rows, cols, meanMatrix);

    printf("%u %u\n", rows, cols);
    for (unsigned r = 0; r < rows; ++r)
    {
        for (unsigned c = 0; c < cols; ++c)
        {
            printf("%f ", meanMatrix[r][c]);
        }
        puts("");
    }
}
