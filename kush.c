/*  to compile and run:
 *  gcc kush.c -o kush
 *  ./kush
 */

#include "kush.h"

int main(void)
{
    const char word1[] = {"help"};
    const char word2[] = {"helps"};
    int result = other_equals(word1, word2);
    char* output;
    *output = result + '0';
    write(OUT, output, sizeof(output));
    int size = string_size(word1);
    char* sizeo;
    *sizeo = size + '0';
    write(OUT, sizeo, sizeof(sizeo));
    const char prompt[] = {TREE};
prompt_start:
    write(OUT, prompt, sizeof(prompt));
    char input[INSIZE];
    read(IN, input, INSIZE);
    write(OUT, input, INSIZE);
    if(equals(input, sizeof(input), "exit") == 0)
        exit(0);
    else
        goto prompt_start;
}

int cat(const char* input)
{
    return 0;
}

int cp(const char* input)
{
    return 0;
}

int ls() 
{
    return 0;
}

int grep(const char* input)
{
    return 0;
}

int equals(const char* src, int size, const char* cmp)
{
    const char* source = src;
    const char* compare = cmp;
    for(int i = 0; i < size; i++)
    {
        if(*source != *compare)
            return 1;
        source++;
        compare++;
    }
    return 0;
}

int other_equals(const char* src, const char* cmp)
{
    while(*src != '\0')
    {
        if(*src != *cmp)
            return 1;
        src++;
        cmp++;
    }  
    return 0;
}

int string_size(const char* src)
{
    const char* s = src;
    int i = 0;
    while(*s != '\0')
    {
        ++i;
        s++;
    }
    return i;
}
