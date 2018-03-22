#include "mycommands.h"

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

int main() {
    const char prompt[] = "ksh$ ";
    char input[80];
    const char d[] = " \n";
    printf("Welcome to the Kennesaw Shell!\nType 'help' for available commands.\n");
    do {
        printf("%s", prompt);
        fflush(stdout);
        fgets(input, 80, stdin);
        const char* token = strtok(input, d);
        if (strcmp(token, "ls") == 0) {
            const char* arg = strtok(NULL, d);
            if(arg == NULL) {
                ls();
            }
            else if (strcmp(arg, "-l") == 0) {
                l();
            }
            else {
                printf("failure");
            }
        }
        else if (strcmp(token, "cat") == 0) {
            char* filename = strtok(NULL, d);
            cat(filename);
        }
        else if (strcmp(token, "cp") == 0) {
            char* src = strtok(NULL, d);
            if (src != NULL)
            {
                const char *dest = strtok(NULL, d);
                if (dest != NULL)
                    cp(src, dest);
                else
                    printf("Not a valid ls argument1\n");
            }
            else
                printf("Not a valid ls argument2\n");
        }
        else if (strcmp(token, "grep") == 0) {
            grep();
        }
        else if (strcmp(token, "help") == 0) {
            help();
        }
        else {
            if(strcmp("exit", token) != 0)
                printf("Not a valid command\n");
        }
    } while (strcmp("exit", input) != 0);
    
    return 0;
}
