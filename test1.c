#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv [])
{
        pid_t pid;
        pid = fork ();
        pid = fork ();
        pid = fork ();
        pid = fork ();
        pid = fork ();
       
        if (pid == 1)
               printf (“hello world”);       
}
