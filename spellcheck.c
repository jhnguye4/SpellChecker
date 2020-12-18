/**
*@file spellcheck.c
*@author Jonathan Nguyen (jhnguye4)
*This program is used to check if certain words in the input file
*are valid or not. If pronoun, they will be blue, if invalid they
*will be red, and black if they are a valid word.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordlist.h"
#include "document.h"
/**
* minimum number of words for the command line
*/
#define TWO 2

/**
*This is the main function that calls upon the functions in document and wordlist to check if the
*input file has invalid words or pronouns
*@return 0 for success status
*@return EXIT_FAILURE for fail status
*/
int main(int argc, char *argv[])
{
  FILE *fp;
  if (argc < TWO){
    fprintf(stderr, "usage: spellcheck<word-file>* <document-file>\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++)
  {
    if ((fp = fopen(argv[i], "r")) == NULL)
    {
      fprintf(stderr, "Can't open file: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
    if (i == argc - 1){
      checkDocument(argv[argc - 1]);
      continue;
    }
    readWords(argv[i]);
    
  }
  fclose(fp);
  return 0;
}
