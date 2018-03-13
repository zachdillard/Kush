/*  to compile and run:
 *  gcc kush.c -o kush
 *  ./kush
 */

#include "kush.h"

int main(void)
{
    const char prompt[PSIZE] = {TREE};
prompt_start:
    write(OUT, prompt, PSIZE);
    char input[INSIZE];
    read(IN, input, INSIZE);
    write(OUT, input, INSIZE);
    goto prompt_start;
    exit(0);
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
