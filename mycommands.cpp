#include "mycommands.h"


#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <dirent.h>

extern char* commands[];
extern size_t command_count;
extern char** environ;

#define _GNU_SOURCE
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int stat(char* path)
{
    struct stat buffer;
    const char* cpath = path;
    FILE* file = fopen(cpath, "r");
    if (file == NULL)
    {
        printf("stat: cannot stat '%s': No such file or directory", cpath);
        return 1;
    }
    stat(cpath, &buffer);
    char* mode;
    if (S_ISREG(buffer.st_mode))
        mode = "file";
    else if (S_ISDIR(buffer.st_mode))
        mode = "directory";
    else
        mode = "unknown";
    char* filename = basename(path);
    printf("  File: %s\n", filename);
    printf("  Size: %jd\t", buffer.st_size);
    printf("Blocks: %llu\t", (unsigned long long) buffer.st_blocks);
    printf("IO Block: %llu\t", (unsigned long long) buffer.st_blksize);
    printf("%s\n", mode);
    printf("Device: %u\t", buffer.st_dev);
    printf("Inode: %u\t", buffer.st_ino);
    printf("Links: %u\n", buffer.st_nlink);
    
    long int access = buffer.st_atime;
    long int modify = buffer.st_mtime;
    long int status = buffer.st_ctime;
    
    printf("%l\n", access);
    return 0;
}

int cat(const char* filename) {
    FILE* file;
    if((file = fopen(filename, "r")) == NULL)
    {
        printf("cat: %s: no such file or directory found\n", filename);
    }
    else
    {
        int getFileContents = fgetc(file);
        while(getFileContents != EOF)
        {
            printf("%c", getFileContents);
            getFileContents = fgetc(file);
        }
    }
    fclose(file);
    return 0;
}

int napTime(const char* seconds){

    int s = atoi(seconds);
    unsigned int t = s;

    printf("I'm going to sleep for %d seconds! \n", s);

    sleep(t);

    printf("What a great nap. I'm back! \n");


}

int killProcess(const char* pids, const char* sigs){


    pid_t pid = atoi(pids);
    int sig = atoi(sigs);

    if (kill(pid, sig) == 0) {
        printf("Process %d terminated \n", pid);
    }



}

int cd(void){

    char *home;
    home = getenv("HOME");

    chdir(home);
    return 0;
}


int cd2(const char* arg){
    DIR* dir = opendir(arg);
    if(dir){
        chdir(arg);
    }
    else{
        printf("%s is not a valid directory", arg);
    }
}

    int ls(void) {
        DIR *dir;
        struct dirent *dp;
        char *file_name;
        dir = opendir("."); //opens at current directory
        int i = 0;
        while ((dp = readdir(dir)) != NULL) { //if first entry in dirent structure is null
            if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
                continue;
            } else {
                file_name = dp->d_name; // file_name is allocated to char pointer
                if (strncmp(file_name, ".", strlen(".")) != 0) {
                    if ((i % 4 == 0) && (i != 0))
                        printf("\n");
                    printf("%-15s\t\n", file_name); //print directory
                    ++i;
                }
            }
        }
        printf("\n");
        closedir(dir);
        return 0;
    }

    int l(void) {        //to go with ls function as ls -l
        DIR *dir;
        struct dirent *dp;
        struct stat fileStat;
        char *file_name;
        char buf[512];
        dir = opendir(".");
        char *t;
        printf("Permissions   SLinks  Size  Type      Last Accessed\t    Name\n");
        while ((dp = readdir(dir)) != NULL) {
            if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
                continue;
            } else {
                file_name = dp->d_name; // store directory name in file_name
                sprintf(buf, "%s", file_name);
                stat(buf, &fileStat);
                t = ctime(&fileStat.st_atime);
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");//user read
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");//user write
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");//user execute
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");//group read
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");//group write
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");//group execute
                printf((fileStat.st_mode & S_IROTH) ? "r" : "-");//others read
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");//others write
                printf((fileStat.st_mode & S_IXOTH) ? "x\t" : "-\t");//others execute
                printf("%-5d ", fileStat.st_nlink);
                int max_width, value;
                max_width = 8;
                value = fileStat.st_size;
                printf("%-5d ", value);

                switch (fileStat.st_mode & S_IFMT) {
                    case S_IFBLK:
                        printf("%-5s", "b  ");
                        break; //Block special file
                    case S_IFCHR:
                        printf("%-5s", "c  ");
                        break; //Character special file
                    case S_IFDIR:
                        printf("%-5s", "d  ");
                        break; //Directory file
                    case S_IFIFO:
                        printf("%-5s", "p  ");
                        break; //FIFO or pipe
                    case S_IFLNK:
                        printf("%-5s", "l  ");
                        break; //Symbolic link
                    case S_IFSOCK:
                        printf("%-5s", "s  ");
                        break; //Socket
                    case S_IFREG:
                        printf("%-5s", "r  ");
                        break; //regular file
                        //File type isn't identified
                    default:
                        printf("%-5s", "-  ");
                        break;
                }
            }
            if (t[strlen(t) - 1] == '\n')
                t[strlen(t) - 1] = '\0';
            printf("%-10s  ", t);
            printf("%-10s \n", file_name); //print directory
        }
        closedir(dir);
        return 0;
    }

    int cp(const char *src, const char *dest) {
        FILE *f1;
        FILE *f2;
        long length;

        f1 = fopen(src, "r");
        f2 = fopen(dest, "w");
        if (f1 == NULL || f2 == NULL)
            return 3;
        fseek(f1, 0L, SEEK_END);
        length = ftell(f1);
        rewind(f1);

        char *buf = (char *) malloc(sizeof(char) * length);
        size_t bytes = fread(buf, length, sizeof(char), f1);
        bytes = fwrite(buf, length, sizeof(char), f2);

        fclose(f1);
        fclose(f2);
        free(buf);
        return 0;
    }

    int grep(const char *input, const char *filename) {
        char *line = NULL;
        size_t length = 0;
        ssize_t read;
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("grep: %s: no such file or directory\n", filename);
            return 1;
        }
        while ((read = getline(&line, &length, file)) != -1) {
            if (strstr(line, input) != NULL)
                printf("%s:%s", filename, line);
        }
        return 0;
    }

int diff(const char* file1, const char* file2)
{
    char file1array[1000][100], file2array[1000][100], *line = NULL;
	size_t length = 0;
    int lines1 = 0;
	int lines2 = 0;
    int read1 =0, read2 =0;
    FILE *f1, *f2; 
	
    f1 = fopen(file1, "r");
    if(f1 == NULL) {printf("file 1 cannot be opened\n"); return 1;}
	
    f2 = fopen(file2, "r");
    if(f2 == NULL) {printf("file 2 cannot be opened\n"); return 1;}
	
	while(fgets (file1array[lines1] , 100 , f1) != NULL)
	{
		if(lines1 == 1000)
		{
			printf("Error. Too many lines in file1.\n");
			return 1;
		}
		++lines1;
	}
	
	length = 0;
	while(fgets (file2array[lines2] , 100 , f2) != NULL)
	{
		if(lines2 == 1000)
		{
			printf("Error. Too many lines in file2.\n");
			return 1;
		}
		++lines2;
	}
	
	int *l1, *l2;
	l1 = (int*)calloc(lines1, sizeof(int));
	l2 = (int*)calloc(lines2, sizeof(int));
	
	//if l1[i] || l2[j] == 0:unchecked, 1:remove, 2:add, 3:leave
	for(int i =0; i < lines1; ++i)
	{
		for(int j =0; j < lines2; ++j)
		{
			while(l2[j] != 0)
				++j;
			if(strcmp(file1array[i],file2array[j])==0)
			{l1[i] = 3; l2[j] = 3;}
			
			
		}
	}
	
	int *save = (int*) malloc(lines1*sizeof(int));
	int save_spot =0;
	//prints removals from file 1
	for(int i = 0; i < lines1; ++i)
	{ 
		if(l1[i] == 0) 
		{
			save[save_spot] = i;
			save_spot++;
		}
	}
	int orig =0;
	for(int i = 0; i < save_spot; ++i)
	{
		orig = i;
		printf("%d", (save[i]+1));
		if(i +1 < save_spot && save[i+1] == save[i]+1)
		{
			while(i+1 < save_spot && save[i+1] == save[i]+1)
				++i;
			printf(",%d", (save[i]+1));
		}
		printf("d");
		int loc = 0;
		int j =0;
		while(loc == 0 && j < lines2)
		{
			if(strcmp(file1array[save[i]+1], file2array[j]) ==0)
				loc = j;
			else
				j++;
		}
		printf("%d\n", loc);
		while(orig <= i)
		{
			printf("< %s\n", file1array[save[orig]]);
			orig++;
		}
	}
	free(save);
	
	//prints additions from file2
	save = (int*) malloc(lines1*sizeof(int));
	save_spot = 0;
	for(int j = 0; j < lines2; ++j)
	{ 
		if(l2[j] == 0) 
		{
			save[save_spot] = j;
			save_spot++;
		}
	}
	orig =0;
	for(int j = 0; j < save_spot; ++j)
	{
		orig = j;
		printf("%d", save[j]+1);
		if(j +1 < save_spot && save[j+1] == save[j]+1)
		{
			while(j+1 < save_spot && save[j+1] == save[j]+1)
				++j;
			printf(",%d", save[j]+1);
		}
		printf("a");
		int loc = 0;
		int i =0;
		while(loc == 0 && i < lines1)
		{
			if(strcmp(file2array[save[j]+1],file1array[i]) == 0)
				loc = i;
			else
				i++;
		}
		printf("%d\n", loc);
		while(orig <= j)
		{
			printf("> %s\n", file2array[save[orig]]);
			orig++;
		}
	}
	
    free(save);
	fclose(f1);
    fclose(f2);
	free(l1);
	free(l2);
	return 0;
}

	int mkdir(const char* dir)
	{
		DIR* d = opendir(dir);
		if(d) //directory exists
		{
			printf("Directory %s already exists\n", dir);
			closedir(d);
			return 0;
		}
		else
		{
			int i = mkdir(dir, S_IRWXU);
			if(i == 0) //successful make
			{
				printf("Directory %s successfully created\n", dir);
				return 0;
			
			}
			else //other error occured
			{
				printf("Error making directory %s\n", dir);
				return 1;
			}
		}
	}
//gives segmentation fault currently
int env()
{
	int i = 0;
	char *s = *environ;

	for(; s; i++)
	{
		printf("%s\n", s);
		s = *(environ+i);
	}
	return i;
}

	int rmd(const char* dir)
	{
		DIR* d = opendir(dir);
		if(d)
		{
			int n =0;
			struct dirent *entry;
			entry = readdir(d);
			while(entry != NULL)
			{
				++n;
				entry = readdir(d);
			}
			if(n <= 2)
			{
				closedir(d);
				remove(dir);
				printf("Directory %s removed\n", dir);
			}
			else
			{
				closedir(d);
				printf("Files found in %s, delete files before removing directory\n", dir);
				return 1;
			}
		}
		else
		{
			printf("Directory %s not found\n", dir);
			return 1;
		}
	}

    void help(void) {
        size_t command_count = 7;
        char *commands[] = {
                "help",
                "clear",
                "exit",
                "cat",
                "ls",
                "cp",
                "grep"
        };
        for (int i = 0; i < command_count; i++) {
            if ((i % 4) == 0 && i != 0)
                printf("\n");
            printf("%-4s\t", commands[i]);
        }
        printf("\n");
    }

    void clear(void) {
        printf("\33[0;0H"); //move cursor to the top
        printf("\33[2J"); //clear screen
    }
