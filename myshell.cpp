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
#include <pwd.h>

//timeout class used for timeout command
class Timeout;
static Timeout * global_timeout_instance = 0;

class Timeout {
public:
	int m_timeout;
	jmp_buf env;

	Timeout(int timeout) : m_timeout(timeout) {
		if (global_timeout_instance) {
			throw "Timeout already in use";
		}
		global_timeout_instance = this;
	}

	~Timeout() {
		stop();
		global_timeout_instance = 0;
	}

	static void alarm_handler(int signum) {
		longjmp(global_timeout_instance->env, 1);
	}

	void start() {
		Timeout * ptr = this;
		if (setjmp(env) != 0) {
			// Don't do anything except throw here, since the state
			// is... funky...
			printf("Alarm fired\n", ptr);
			throw global_timeout_instance;
		}
		signal(SIGALRM, alarm_handler);
		alarm(m_timeout);
		printf("Alarm set\n", ptr);
	}

	void stop() {
		alarm(0);
	}
};
// end class


int main() {
    const char prompt[] = "ksh$ ";
    char cwd[1024];
    char input[80];
    const char d[] = " \n";
    printf("Welcome to the Kennesaw Shell!\nType 'help' for available commands.\n");
    do {
        getcwd(cwd, sizeof(cwd));
        printf("%s " , cwd);
        printf("%s ", prompt);
        fflush(stdout);
        fgets(input, 80, stdin);
        const char* token = strtok(input, d);
       if (strcmp(token, "stat") == 0) {
		char* path = strtok(NULL, d);
		stat(path);
       }
       else if (strcmp(token, "ls") == 0) {
            const char* arg = strtok(NULL, d);
            if(arg == NULL) {
                ls();
            }
            else if (strcmp(arg, "-l") == 0) {
                l();
            }
            else {
                printf("ls: illegal operation %s\n", arg);
            }
        }
        else if(strcmp(token, "kill") == 0){

            const char* pid = strtok(NULL, d);
            const char* sig = strtok(NULL, d);
            if(pid == NULL || sig == NULL){
                printf("Error: null argument. Process id and signal number needed. \n");
            }
            else {
                killProcess(pid, sig);
            }
        }
        else if(strcmp(token, "sleep")==0){
            const char* seconds = strtok(NULL, d);
            if(seconds == NULL){
                printf("Error: seconds must be declared \n");
            }
            else {
                napTime(seconds);
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
                    printf("cp: %s: not a valid file or directory\n", dest);
            }
            else
                printf("cp: %s: not a valid file or directory\n", src);
        }
        else if (strcmp(token, "grep") == 0) {
            char* search = strtok(NULL, d);
            char* file;
            while((file = strtok(NULL, d)) != NULL) {
                grep(search, file);
            }
        }
        else if (strcmp(token, "cd") == 0) {
            const char* arg = strtok(NULL, d);
            if(arg == NULL) {
                cd();
            }
            else if(arg != NULL){
		DIR* dir = opendir(arg);
		if(dir != NULL)
                    cd2(arg);

            }
            else {
                printf("cd: illegal operation %s\n", arg);
            }
        }
	else if (strcmp(token, "diff") == 0) {
            char* file1 = strtok(NULL, d);
            if (file1 != NULL)
            {
                const char *file2 = strtok(NULL, d);
                if (file2 != NULL)
                    diff(file1, file2);
                else
                    printf("diff: %s: not a valid file or directory\n", file2);
            }
            else
                printf("diff: %s: not a valid file or directory\n", file1);
        }
	else if(strcmp(token, "mkdir") == 0) {
		char * dir = strtok(NULL, d);
		if(dir != NULL)
			mkdir(dir);
		else
			printf("mkdir: please provide directory path\n");
	}
	else if(strcmp(token, "rmdir") == 0) {
			char * dir = strtok(NULL, d);
			if(dir != NULL)
				rmd(dir);
			else
				printf("rmdir: please provide directory path\n");
		}

	else if(strcmp(token, "waitfor") == 0) {
		char* argc = strtok(NULL, d);
		if(argc != NULL)
			waitfor(argc);
		else
			printf("The child process is not a valid process.\n");
	}
        else if (strcmp(token, "help") == 0) {
            help();
        }
        else if (strcmp(token, "clear") == 0) {
            clear();
        }
	else if(strcmp(token, "env") == 0) {
		env();
	}
	else if(strcmp(token, "timeout") == 0)
		{
			char* t = strtok(NULL, d);
			int time = atoi(t);
			
			//timeout try begin 
			try{
				Timeout timeout(time); timeout.start();
				char* tok = strtok(NULL, d);
				if (strcmp(token, "stat") == 0) {
					char* path = strtok(NULL, d);
					stat(path);
      				}
       				else if (strcmp(token, "ls") == 0) {
            				const char* arg = strtok(NULL, d);
            				if(arg == NULL) {
                				ls();
            				}
            				else if (strcmp(arg, "-l") == 0) {
                				l();
            				}
            				else {
                				printf("ls: illegal operation %s\n", arg);
            				}
        			}
      	  			else if(strcmp(token, "kill") == 0){

            				const char* pid = strtok(NULL, d);
            				const char* sig = strtok(NULL, d);
            				if(pid == NULL || sig == NULL){
                				printf("Error: null argument. Process id and signal number needed. \n");
           				}
            				else {
                				killProcess(pid, sig);
            				}
        			}
        			else if(strcmp(token, "sleep")==0){
            				const char* seconds = strtok(NULL, d);
            				if(seconds == NULL){
                				printf("Error: seconds must be declared \n");
            				}
            				else {
                				napTime(seconds);
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
                    					printf("cp: %s: not a valid file or directory\n", dest);
            				}
            				else
                				printf("cp: %s: not a valid file or directory\n", src);
        			}
        			else if (strcmp(token, "grep") == 0) {
            				char* search = strtok(NULL, d);
            				char* file;
            				while((file = strtok(NULL, d)) != NULL) {
                				grep(search, file);
            				}
        			}
        			else if (strcmp(token, "cd") == 0) {
            				const char* arg = strtok(NULL, d);
            				if(arg == NULL) {
                				cd();
            				}
            				else if(arg != NULL){
						DIR* dir = opendir(arg);
						if(dir != NULL)
                    					cd2(arg);

            				}
            				else {
                				printf("cd: illegal operation %s\n", arg);
            				}
        			}
				else if (strcmp(token, "diff") == 0) {
            				char* file1 = strtok(NULL, d);
            				if (file1 != NULL)
            				{
                				const char *file2 = strtok(NULL, d);
                				if (file2 != NULL)
                    					diff(file1, file2);
                				else
                    					printf("diff: %s: not a valid file or directory\n", file2);
            				}
            				else
                				printf("diff: %s: not a valid file or directory\n", file1);
        			}
				else if(strcmp(token, "mkdir") == 0) {
					char * dir = strtok(NULL, d);
					if(dir != NULL)
						mkdir(dir);
					else
						printf("mkdir: please provide directory path\n");
				}
				else if(strcmp(token, "rmdir") == 0) {
					char * dir = strtok(NULL, d);
					if(dir != NULL)
						rmd(dir);
					else
						printf("rmdir: please provide directory path\n");
				}
				else if(strcmp(token, "waitfor") == 0) {
					char* argc = strtok(NULL, d);
					if(argc != NULL)
						waitfor(argc);
					else
						printf("The child process is not a valid process.\n");
				}
        			else if (strcmp(token, "help") == 0) {
            				help();
        			}
        			else if (strcmp(token, "clear") == 0) {
            				clear();
        			}
				else if(strcmp(token, "env") == 0) {
					env();
				}
				else
					printf("timeout: %s command not found\n", token);
			}
			catch(Timeout *t)
			{
				printf("Timer experied\n");
			}
			//timeout end
			
		}
        else {
            if(strcmp("exit", token) != 0)
                printf("ksh: %s: command not found\n", token);
        }
    } while (strcmp("exit", input) != 0);
    
    return 0;
}
