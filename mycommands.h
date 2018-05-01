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

//Sends kill signal to process
//Author: Pablo Novoa
int killProcess(const char* pids, const char* sigs);

//Sends sleep signal for specified time
//Author: Pablo Novoa

int napTime(const char* seconds);


//Changes current working directory to home directory
//Author: Pablo Novoa
int cd(void);
//Changes current working directory to specified directory.
//Author: Pablo Novoa
int cd2(const char* arg);

//Copy contents of one file to another location
//Author: Jacob Crumbley
int cp(const char* src, const char* dest);

//Searches for a string in a file and if found,
//returns the line its found on
//Author: Zach Dillard
int grep(const char* search, const char* file);

//prints changes needed to be made to file1 to
//produce file 2
//Author: Jacob Crumbley
int diff(const char* file1, const char* file2);

//makes a new directory if not made at dir
//Author: Jacob Crumbley
int mkdir(const char* dir);

//prints out all environment variables
//Author: Brett Warner
int env();

void help(void);
void clear(void);

#endif // MYCOMMANDS_H
