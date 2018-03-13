#include <unistd.h>
#include <stdlib.h>

#define IN 0
#define OUT 1
#define ERR 2

#define TREE 0xF0, 0x9F, 0x8C, 0xB2, '\0'
#define PSIZE 5
#define INSIZE 32

int cat(const char* input);
int cp(const char* input);
int ls();
int grep(const char* input);
