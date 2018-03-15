#include <unistd.h>
#include <stdlib.h>

#define IN 0
#define OUT 1
#define ERR 2

#define TREE 0xF0, 0x9F, 0x8C, 0xB2, '\0'
#define PSIZE 5
#define INSIZE 32

void string_clear(char* input, unsigned int size) {
    for(int i = 0; i < size; i++)
    *input++ = '\0';
}

int string_size(const char* src) {
    int i = 0;
    while(*src != '\0') {
        i++;
        src++;
    }
    return i;
}

int string_equals(const char* src, const char* cmp) {
    if(string_size(src) != string_size(cmp))
        return 0;
    while(*src != '\0') {
        if(*src != *cmp)
            return 0;
        src++;
        cmp++;
    }
    return 1;
}

//experimental print function
void print(const char* string) {
    write(OUT, string, sizeof(string));
}

int cat(const char* filename) {return 0;}
int ls(void) {return 0;}
int cp(const char* src, const char* dest) {return 0;}
int grep(const char* string, const char* filename) {return 0;}

//for right now it can only parse the actual command
//and not any options, for example:
//can do
//      cp
//but not
//      cp file1 file2
int is_command(const char* cmd) {
    if(string_equals(cmd, "cat\n")) 
        return 1;
    else if(string_equals(cmd, "ls\n"))
        return 1;
    else if(string_equals(cmd, "cp\n"))
        return 1;
    else if(string_equals(cmd, "grep\n"))
        return 1;
    else
        return 0;
}

int main() {
    const char prompt[] = {TREE + ' '};
prompt_start:
    write(OUT, prompt, sizeof(prompt));
    char input[INSIZE];
    string_clear(input, INSIZE);
    read(IN, input, INSIZE);
    if(string_equals(input, "exit\n"))
       return 0;
    else {
        if(is_command(input))
            write(OUT, "valid kush command\n", 20);
        else
            write(OUT, "not a valid kush command\n", 25);
        goto prompt_start;
    }
}
