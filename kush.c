#include <unistd.h>
#include <stdlib.h>

#define IN 0
#define OUT 1
#define ERR 2

#define TREE 0xF0, 0x9F, 0x8C, 0xB2, '\0'
#define PSIZE 5
#define INSIZE 32

//Prints a tree emoji to stdout and then wait for input
//from stdin. It then echos whatever was input.
//Typing more than 32 characters causes undefined behavior

//The terminal used to run this program must support unicode
//or you will see a random symbol for the prompt

int main(void)
{
    const char prompt[PSIZE] = {TREE};
    write(OUT, prompt, PSIZE);
    char input[INSIZE];
    read(IN, input, INSIZE);
    write(OUT, input, INSIZE);
    exit(0);
}
