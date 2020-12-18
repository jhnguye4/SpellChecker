/**
*@file document.c
*@author Jonathan Nguyen (jhnguye4)
*This program is used to read in input document and
*calls upon lookupWord from wordlist to compre each word to
*the wordlist to see if its valid or not.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "wordlist.h"
/**
* Maximum length of line
*/
#define MAX_LINE 75
/**
* ASCI for making color red
*/
#define RED "\x1b[31m"
/**
* ASCI for making color blue
*/
#define BLUE "\x1b[34m"
/**
* ASCI for making color back to default
*/
#define END "\x1b[0m"

/**
*Given a line of text from the document, this function
*finds each word in the line, checks it against the word
*list and prints the line, highlighted as necessary. The
*two flags passed to this function tell it about whether
*the input line had to be truncated when it was read. If it
*did, the ellipsis flag tells the function to print out an
*ellipsis at the end of the line. If the chopped flag is true, it
*tells the function that the last word on the line was chopped and
*shouldn't be spellchecked.
*@param line[] is the 1D array of max 75 chars is passed in that will be
*checked to see words are valid. It will print word if it is valid.
*@param ellipsis, if true that means that the array reached its max
*and that ... will be attached to the end of print
*@param chopped, if true that means that the last word was cut off and
*that word will not be checked for mispelling
*/
static void checkLine( char const line[], bool ellipsis, bool chopped)
{
  int s = strlen(line);
  char word[s+1];
  if (chopped && ellipsis) {
    for (int k = 0; k <= s; k++){
      char curr = line[k];
      int i = 0;
      while (wordChar(curr)){
        word[i] = curr;
        i++;
        k++;
        curr = line[k];
      }
      word[i] = '\0';
      i = 0;
      if (curr == '\0'){
        printf("%s...\n", word);
        break;
      }
      if (wordChar(word[i])){
        int type = lookupWord(word);
        if (type == -1){
          char newWord[] = RED;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }
        if (type == 0){
          printf("%s", word);
        }
        if (type == 1){
          char newWord[]=BLUE;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }
      }

      if (!wordChar(curr) && curr != '\0'){
        printf("%c", curr);
        
      }
      

      for (int j = 0; j < s; j++){
        word[j] = '\0';
      }
    }
  }
  else if (!chopped && ellipsis) {
    for (int k = 0; k <= s; k++){
      char curr = line[k];
      int i = 0;
      while (wordChar(curr)){
        word[i] = curr;
        i++;
        k++;
        curr = line[k];
      }
      word[i] = '\0';
      i = 0;
      
      if (wordChar(word[i])){
        int type = lookupWord(word);

        if (type == -1){
          char newWord[] = RED;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }

        if (type == 0){
          printf("%s", word);
        }

        if (type == 1){
          char newWord[]=BLUE;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }
      }

      if (!wordChar(curr) && curr != '\0'){
        printf("%c", curr);
        
      }
      if (curr == '\0'){
        printf("...\n");
      }

      for (int j = 0; j < s; j++){
        word[j] = '\0';
      }
    }
  }
  else {
    for (int k = 0; k <= s; k++){
      char curr = line[k];
      int i = 0;
      while (wordChar(curr)){
        word[i] = curr;
        i++;
        k++;
        curr = line[k];
      }
      word[i] = '\0';
      i = 0;
      
      if (wordChar(word[i])){
        int type = lookupWord(word);
        
        if (type == -1){
          char newWord[] = RED;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }

        if (type == 0){
          printf("%s", word);
        }

        if (type == 1){
          char newWord[]=BLUE;
          strcat(newWord, word);
          strcat(newWord, END);
          printf("%s", newWord);
        }
      }
      
      if (!wordChar(curr) && curr != '\0'){
        printf("%c", curr);
        
      }
      if (curr == '\0'){
        printf("\n");
      }

      for (int j = 0; j < s; j++){
        word[j] = '\0';
      }
    }
  }
}

/**
*It's responsible for reading the input document from the file with the given
*name and printing it out with highlighting (with help from other functions).
*@param fileName is the last command line argument that is passed in and scanned
*line by line and stored in a array that can only hold 75 chars. That array will be
*passed to checkLine, to be checked and printed
*/
void checkDocument(char const fileName[])
{
  FILE *fp;
  fp = fopen(fileName, "r");
  int count = 0;
  int temp;
  char buffer[MAX_LINE + 1];
  for (int i = 0; i < MAX_LINE + 1; i++){
    buffer[i] = '\0';
  }
  while ((temp = fgetc(fp)) != EOF){
    if (temp == '\n' && count < MAX_LINE){
      buffer[count] = '\0';
      checkLine(buffer, false, false);
      count = 0;
      for (int i = 0; i < MAX_LINE + 1; i++){
        buffer[i] = '\0';
      }
      continue;
    }
    if (!wordChar(temp) && count == MAX_LINE){
      while (temp != '\n'){
        temp = fgetc(fp);
      }
      buffer[count] = '\0';
      checkLine(buffer, true, false);
      count = 0;
      for (int i = 0; i < MAX_LINE + 1; i++){
        buffer[i] = '\0';
      }
      continue;
    }
    if (wordChar(temp) && count == MAX_LINE){
      while (temp != '\n'){
        temp = fgetc(fp);
      }
      buffer[count] = '\0';
      checkLine(buffer, true, true);
      count = 0;
      for (int i = 0; i < MAX_LINE + 1; i++){
        buffer[i] = '\0';
      }
      continue;
    }
    
    buffer[count] = temp;
    count++;
  }
}
