#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRLEN 31
#define EXIT_KEYWORD "stop"

int read_string(char str[MAX_STRLEN])
{
    static int i = 0;
    static const char *strings[] =
    {
        "ciao",
        "A",
        "901801901801",
        "ciaociao",
        "pcpcpcpc",
        "mdm",
        EXIT_KEYWORD
    };

    strcpy(str, strings[i++]);
    return 0 == strcmp(str, EXIT_KEYWORD);
}

int is_composite_of_length(const char str[MAX_STRLEN], size_t strLength, size_t tokenLength)
{
    assert(strLength % tokenLength == 0);
    int returnValue = 1;
    for (const char* it = str; it != str + strLength; it += tokenLength)
    {
        if (0 != strncmp(str, it, tokenLength))
        {
            returnValue = 0;
            break;
        }
    }

    return returnValue;
}

size_t is_composite(const char str[MAX_STRLEN], const size_t strLength)
{
    for (size_t i = 1; i <= strLength / 2; ++i)
    {
        if (strLength % i == 0 && 1 == is_composite_of_length(str, strLength, i))
        {
            return i;
        }
    }

    return 0;
}

int main()
{
    char str[MAX_STRLEN] = {0};
    while(!read_string(str))
    {
        const size_t strLength = strlen(str);
        const size_t tokenLength = is_composite(str, strLength);
        if (0 != tokenLength)
        {
            char token[MAX_STRLEN] = {0};
            strncpy(token, str, tokenLength);
            printf("The string '%s' (length %zu) is composite of '%s' (dimension %zu)\n", str, strLength, token, tokenLength);
        }
        else
        {
            printf("The string '%s' (length %zu) is not composite\n", str, strLength);
        }
    }

    return 0;
}
