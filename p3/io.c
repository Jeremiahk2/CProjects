/**
  @file io.c
  @author Jeremiah Knizley
  File responsible for hyandling lines of text from an input file
  and printing them with color highlighting as needed
  */

#include "io.h"
#include <stdlib.h>
#include <string.h>

/**
  Counts and returns the number of lines in an input file.
  Checks the length of each line, if they are greater than LINE_LIMIT, the program terminates.
  Rewinds file afterwards.
  @param fp the input file to scan
  @return int the number of lines in the file
  */
int countLines(FILE *fp) 
{
  int matches = 0;
  int numLines = 0;
  char nextChar;
  while (matches != EOF) {
    //+1 is for the null terminator
    char str[LINE_LIMIT + 1];
    //Find a sequence of up to 100 characters until the newline pops up. New line won't be consumed though.
    matches = fscanf(fp, "%100[^\n]", str);
    //This should either be a random character, meaning the line was too long, or it'll be a new line or EOF which means the line wasn't too long.
    //If it's just a new line, we need to consume it anyway to read the next line.
    nextChar = fgetc(fp);
    //if the array is full, but the next char isn't a new line or EOF, the line was too long.
    if (strlen(str) == LINE_LIMIT && (nextChar != '\n' && nextChar != EOF)) {
      fprintf(stderr, "Input line too long\n");
      exit(1);
    }
    //increase the number of lines.
    numLines++;
  }
  //Normally if the file ended without a new line, we would need to decrement numLines because the loop would run an extra time for processing EOF at the end of the last line.
  //But if the file ends with a new line (the last line is empty), we don't want to decrement it because that line counts.
  //So we check nextChar, because that should be the last line in the file, to see if it ended with a new line.
  if (nextChar != '\n') {
    numLines--;
  }
  //rewind file, return.
  rewind(fp);
  return numLines;
}

/**
  reads the next line from the given file and stores it in the given string.
  Returns true if there is another line to read, and false otherwise.
  */
bool readLine(FILE *fp, char line[LINE_LIMIT + 1])
{
  //get next line
  fscanf(fp, "%100[^\n]", line);
  char next = fgetc(fp);
  //if there is another line, return true
  if (next == '\n') {
    return true;
  }
  //if not, false
  return false;
}

/**
  prints the given line to standard output. The given color array should have an element
  for each character of the line. DEFAULT_COLOR means default, IDENT_COLOR means it will be printed red
  OP_COLOR means a character should be printed blue
  */
void printLine(char line[LINE_LIMIT + 1], int color[LINE_LIMIT])
{
  //Set old to default, so that the first iteration will just print the character like normal (if it's supposed to)
  int old = DEFAULT_COLOR;
  for (int i = 0; line[i]; i++) {
    //if the previous character was default, but the new one is INDENT, print the character with the red hexcode
    if (old == DEFAULT_COLOR && color[i] == IDENT_COLOR) {
      printf("\x1b\x5b\x33\x31\x6d%c", line[i]);
    }
    //If the old color was also red, then print the character without the hexcode (because the color is already red)
    else if (color[i] == IDENT_COLOR) {
      putchar(line[i]);
    }
    //If the old color was indented, but the new one is default, print the character with the default hexcode
    if (old == IDENT_COLOR && color[i] == DEFAULT_COLOR) {
      printf("\x1b\x5b\x30\x6d%c", line[i]);
    }
    //If the old color is already default, just print the character like normal (because the color is already default).
    else if (color[i] == DEFAULT_COLOR) {
      putchar(line[i]);
    }
    //Update old for the next iteration
    old = color[i];
  }
  if (old == IDENT_COLOR) {
    printf("\x1b\x5b\x30\x6d");
  }
  putchar('\n');
}
