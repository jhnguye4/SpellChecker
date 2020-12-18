/**
*@file wordlist.c
*@author Jonathan Nguyen (jhnguye4)
*This program is used to read in input files and
* create a word list that can be used later to see if
* words are valid or not
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
/**
* Maximum number of words for list
*/
#define MAX_WORDS 40000
/**
* Maximum length of word with null terminator
*/
#define WORD_LENGTH 13
#define LARGE_WORD  75

static char wordlist[MAX_WORDS][WORD_LENGTH];
static int row = 0;

/**
*This is part of the wordlist component. Given a
*character, it returns true if that character is one that can be part of a word.
*@param ch is the character being passed in
*@return true if it is valid and false if not valid character
*/
bool wordChar(char ch)
{
  return ( ch >= 'a' && ch <= 'z' ) ||
    ( ch >= 'A' && ch <= 'Z' ) ||
    ch == '\'';
}

/**
*Given a word from the document, it looks it up in the word list and
*returns one of three values. Either the given word is a proper noun,
*or it's a regular word that's spelled correctly, or it's a word that
*doesn't match anything on the word list. Use the preprocessor to
*define a named constant for each of these possible return values.
*@param is a 1D array of chars
*@return int, 0 for valid word, -1 for invalid, 1 for pronoun
*/
int lookupWord(char const word[])
{
  bool found = false;
  char word2[WORD_LENGTH];
  int l =0;
  char ch;
  for (int i = 0; i < WORD_LENGTH;i++)
  {
    word2[i] = '\0';
  }

  while (word[l]){
    ch = tolower(word[l]);
    word2[l] = ch;
    l++;
  }
  int s = strlen(word);
  for (int i = 0; i < s; i++)
  {
    if (!wordChar(word[i])){
      return -1;
    }
  }
  
  for (int i = 0; i < row; i++)
  {
    if ((strcmp(wordlist[i], word))==0){
      char ch;
      for (int j = 0; j < WORD_LENGTH; j++){
        found = true;
        ch = word[j];
        if (ch >='A' && ch <= 'Z'){
          return 1;
        }
      }
    }
    
    if (strcmp(word2, wordlist[i]) == 0){
      return 0;
    }
  }
  
  if (found){
    return 0;
  }
  
  return -1;
}

/**
*Given the name of a file, it opens it, reads all the words from it
*and adds any new (unique) words to the in-memory word list. If any
*error conditions occur, this function or a function called by it can
*print out the right error message and terminate the program.
*@param is the command line argument or words for wordlist
*@return EXIT_FAILURE if there are too many words or invalid word length
*/
void readWords(char const fileName[])
{
  FILE *fp;
  fp = fopen(fileName, "r");
  
  int col = 0;
  int temp;
  
  while ((temp = fgetc(fp)) != EOF){
    char buffer[LARGE_WORD];
    if ( !wordChar(temp)){
      if (temp != '\n'){
        fprintf(stderr, "Invalid word at %s:%d\n", fileName, row +1);
        exit(1);
      }
    }
    if (row == MAX_WORDS){
      fprintf(stderr, "Too many words\n");
      exit(1);
    }

    if (temp == '\n'){
      buffer[col] = '\0';
      bool duplicate = false;
      for (int i = 0; i < row; i++){
        if ((strcmp(buffer, wordlist[i])) == 0){
          duplicate = true;
          break;
        }
      }
      if (!duplicate){
        strcpy(wordlist[row], buffer);
        row++;
      }
      duplicate = false;
      for(int i = 0; i < LARGE_WORD;i++){
        buffer[i] = '\0';
      }
      col = 0;
      continue;
    }

    buffer[col] = temp;
    col++;
  }
}
