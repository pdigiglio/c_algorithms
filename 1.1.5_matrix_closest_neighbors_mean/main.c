#include <assert.h>
#include <stdio.h>

#define MAX_MAT_ROWS 5
#define MAX_MAT_COLS 5

float evaluate_nn_mean(
    int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS],
    size_t row, size_t rows,
    size_t col, size_t cols)
{
    const size_t rowStart = row - (row > 0);
    const size_t rowEnd   = row + (row <= rows - 2) + (row <= rows - 1);

    const size_t colStart = col - (col > 0);
    const size_t colEnd   = col + (col <= cols - 2) + (col <= cols - 1);

    const size_t count = (rowEnd - rowStart) * (colEnd - colStart) - 1;
    if (0 == count)
        return (float)0;

    int sum = -inputMatrix[row][col];
    for (size_t r = rowStart; r < rowEnd; ++r)
    {
        for (size_t c = colStart; c < colEnd; ++c)
        {
            sum += inputMatrix[r][c];
        }
    }

    return sum / (float)count;
}

void evaluate_nn_means(
    int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS],
    size_t rows, size_t cols,
    float outMatrix[MAX_MAT_ROWS][MAX_MAT_COLS])
{
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            outMatrix[r][c] = evaluate_nn_mean(inputMatrix, r, rows, c, cols);
        }
    }
}

int main()
{
    size_t rows = 3;
    size_t cols = 4;

    int inputMatrix[MAX_MAT_ROWS][MAX_MAT_COLS] =
    {
        { 1,  2,  3,  4, 0 },
        { 5,  6,  7,  8, 0 },
        { 9, 10, 11, 12, 0 },
        { 0,  0,  0,  0, 0 },
        { 0,  0,  0,  0, 0 }
    };

    float meanMatrix[MAX_MAT_ROWS][MAX_MAT_COLS] = { 0 };
    evaluate_nn_means(inputMatrix, rows, cols, meanMatrix);

    printf("%zu %zu\n", rows, cols);
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            printf("%f ", meanMatrix[r][c]);
        }
        puts("");
    }
}
