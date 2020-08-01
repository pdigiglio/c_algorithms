#include <assert.h>
#include <stdio.h>
#include <string.h>

#define DICTIONARY_MAX_LENGTH 30
#define WORD_MAX_LENGTH 30

typedef struct String
{
    size_t length;
    char data[WORD_MAX_LENGTH];
} String;

void init_string(String* string, const char* str)
{
    strcpy(string->data, str);
    string->length = strlen(string->data);
    if (string->length > WORD_MAX_LENGTH)
    { 
        fprintf(stderr, "Word size too big: '%s' has length %zu (max allowed: %d)\n", str, string->length, WORD_MAX_LENGTH - 1);
        string->length = WORD_MAX_LENGTH;
        string->data[WORD_MAX_LENGTH - 1] = '\0';
    }
}

void swap(String* lhs, String* rhs)
{
    String s;
    s.length = lhs->length;
    strcpy(s.data, lhs->data);

    lhs->length = rhs->length;
    strcpy(lhs->data, rhs->data);

    rhs->length = s.length;
    strcpy(rhs->data, s.data);
}

typedef struct Replacement
{
    String from;
    char to[WORD_MAX_LENGTH];
} Replacement;

void init_replacement(Replacement* replacement)
{
    assert(replacement != NULL);
    init_string(&replacement->from, "");
    memset(replacement->to, 0, WORD_MAX_LENGTH);
}

typedef struct Dictionary
{
    Replacement replacements[DICTIONARY_MAX_LENGTH];
    size_t size;
} Dictionary;

void sort_by_from_length_decreasing(Dictionary* dictionary)
{
    for (size_t i = 0; i < dictionary->size; ++i)
    {
        for (size_t j = i + 1; j < dictionary->size; ++j)
        {
            if (dictionary->replacements[i].from.length < dictionary->replacements[j].from.length)
            {
                swap(&dictionary->replacements[i].from, &dictionary->replacements[j].from);
            }
        }
    }
}

void init_dictionary(Dictionary* dictionary)
{
    assert(dictionary != NULL);
    for (size_t i = 0; i < DICTIONARY_MAX_LENGTH; ++i)
    {
        init_replacement(dictionary->replacements + i);
    }

    dictionary->size = 0;
}

// Return 0 on error; 1 on success.
int read_dictionary(const char* filename, Dictionary* dictionary)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Cannot open dictionary file %s\n", filename);
        return 0;
    }

    int returnValue = 1;
    fscanf(file, "%zu", &(dictionary->size));
    for (size_t i = 0; i < dictionary->size; ++i)
    {
        char* to = dictionary->replacements[i].to;
        char fromBuf[256];
        const int readTokens = fscanf(file, "%s %s", to, fromBuf);
        if (2 != readTokens)
        {
            fprintf(stderr, "Bad input at line %zu\n", i + 1);
            returnValue = 0;
            break;
        }

        init_string(&dictionary->replacements[i].from, fromBuf);
    }

    if (returnValue)
    {
        sort_by_from_length_decreasing(dictionary);
    }

    fclose(file);
    return returnValue;
}

void print_dictionary(const Dictionary *dictionary)
{
    FILE *file = stderr;

    fprintf(file, "%zu\n", dictionary->size);
    for (size_t i = 0; i < dictionary->size; ++i)
    {
        fprintf(file, "%s %s\n", dictionary->replacements[i].to, dictionary->replacements[i].from.data);
    }
}

void print_compressed_word(FILE *outFile, const char* word, const Dictionary* dictionary)
{
    const size_t wordLength = strlen(word);
    size_t w = 0;
    while (w < wordLength)
    {
        int replaced = 0;
        for (size_t i = 0; i < dictionary->size; ++i)
        {
            const size_t fromLength = dictionary->replacements[i].from.length;
            
            // If there are not enough chars, go to the next iteration
            if (fromLength > wordLength - w)
            {
                continue;
            }
           
            if(0 == strncmp(word + w, dictionary->replacements[i].from.data, fromLength))
            {
                fprintf(outFile, "%s", dictionary->replacements[i].to);
                w += fromLength;
                replaced = 1;
                break;
            }
        }

        if (!replaced)
        {
            fprintf(outFile, "%c", word[w++]);
        }
    }
}

FILE* fopen_or_default(const char* filename, const char* mode, FILE* dflt)
{
    FILE *file = fopen(filename, mode);
    return NULL == file ? dflt : file;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <dictionary> [input] [output]\n", argv[0]);
        return 1;
    }

    Dictionary dictionary;
    init_dictionary(&dictionary);

    if (!read_dictionary(argv[1], &dictionary))
    {
        return 1;
    }

    //print_dictionary(&dictionary);

    FILE *const inFile = fopen_or_default(argc > 2 ? argv[2] : "", "r", stdin);
    FILE *const outFile = fopen_or_default(argc > 3 ? argv[3] : "", "w", stdout);

    char buffer[256] = {0};
    while(EOF != fscanf(inFile, "%s", buffer))
    {
        print_compressed_word(outFile, buffer, &dictionary);
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
