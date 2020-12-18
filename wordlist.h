/**
*@file wordlist.h
*@author Jonathan Nguyen (jhnguye4)
* This is the prototype function for wordlist.
*/

#include <stdbool.h>

/*
*
*@param ch
*@return bool, true if it can be solved and false if it cannot
*/
bool wordChar(char ch);

int lookupWord(char const word[]);

void readWords(char const fileName[]);

void printArg();
