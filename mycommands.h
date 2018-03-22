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

//Copy contents of one file to another location
//Author: Jacob Crumbley
int cp(const char* src, const char* dest);

//Searches for a string in a file and if found,
//returns the line its found on
//Author: Zach Dillard
int grep(const char* input);

void help(void);
void clear(void);
