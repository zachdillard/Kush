#ifndef MYCOMMANDS_H_
#define MYCOMMANDS_H_

/***************************************************
    mycommands.h
    Header file for the Kennesaw Shell commands
 ***************************************************/

//Displays contents of file
//Author: Brett Warner
int cat(const char* filename);

//Displays contents of current directory
//Author: Pablo Novoa
int ls(void);

//Helper function to ls
//Author: Pablo Novoa
int l(void);

//Changes current working directory to home directory
//Author: Pablo Novoa
int cd(void);
//Changes current working directory to specified directory.
//Author: Pablo Novoa
int cd2(const char* arg);

//Copy contents of one file to another location
//Author: Jacob Crumbley
int cp(const char* src, const char* dest);

//Sends signal to process to either terminate or kill it
//Author: Pablo Novoa
int killProcess(const char* pid, const char* sig);

//Searches for a string in a file and if found,
//returns the line its found on
//Author: Zach Dillard
int grep(const char* search, const char* file);


void help(void);
void clear(void);

#endif // MYCOMMANDS_H
