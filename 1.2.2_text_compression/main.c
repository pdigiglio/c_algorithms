#include <assert.h>
#include <stdio.h>
#include <string.h>

#define THRESHOLD 3

void print_compressed_word(FILE* outFile, const char *word, size_t threshold)
{
    assert(NULL != outFile);
    const size_t wordLength = strlen(word);
    if (0 == wordLength)
        return;

    size_t referenceIndex = 0;
    for (size_t i = 1; i < wordLength + 1; ++i)
    {
        if(word[referenceIndex] != word[i])
        {
            const size_t repetitionCount = i - referenceIndex;
            if (repetitionCount >= threshold)
            {
                fprintf(outFile, "$%zu$%c", repetitionCount, word[referenceIndex]);
                referenceIndex = i;
            }
            else
            {
                while(referenceIndex != i)
                {
                    fprintf(outFile, "%c", word[referenceIndex++]);
                }
            }
        }
    }
}

FILE* fopen_or_default(const char* filename, const char* mode, FILE* dflt)
{
    FILE *file = fopen(filename, mode);
    return NULL != file ? file : dflt;
}

int main(int argc, const char *argv[])
{
    FILE * const inFile = fopen_or_default((argc > 1) ? argv[1] : "", "r", stdin);
    FILE * const outFile = fopen_or_default((argc > 2) ? argv[2] : "", "w", stdout);

    char buffer[256] = {0};
    while (EOF != fscanf(inFile, "%s", buffer))
    {
        print_compressed_word(outFile, buffer, THRESHOLD);

        const char separator = fgetc(inFile);
        fputc(separator, outFile);
    }

    if (inFile != stdin)
    {
        fclose(inFile);
    }

    if (outFile != stdout)
    {
        fclose(outFile);
    }

    return 0;
}
