/**
  @file input.c
  @author Jeremiah Knizley
  File responsible for reading input for the schedule program.
  Contains a method to read a line of a file 
*/
#include "input.h"


char *readLine(FILE *fp)
{
  //Initialize bool values that will control when the loop will end.
  bool newLineFound = false;
  bool endOfFile = false;
  //Initialize line to hold one character. This will expand as we go.
  //ASIDE: length of 0 seemingly causes problems with scanf, and we always want a null terminator anyway.
  char *line = (char *)malloc(1 * sizeof(char));
  //Need to keep track of the length of "array" of characters.
  int memLength = 1;
  int lineLength = 0;

  while (!(newLineFound || endOfFile)) {
    //Get next char from file.
    char current = fgetc(fp);
    //If it's new line, make a note of it. If it's EOF, make a note of it. If not, put the character in the array.
    if (current == '\n') {
      newLineFound = true;
    }
    else if (current == EOF) {
      endOfFile = true;
    }
    else {
      *(line + lineLength) = current;
      lineLength++;
      //If we are out of memory.
      if (lineLength == memLength) {
        //Resize the line array. We want it to change our memlength, but keep lineLength the same.
        line = realloc(line, memLength *= LINE_INC);
      }
    }
  }
  if (lineLength == 0 && endOfFile) {
    //Still need to free line for the one byte in it
    free(line);
    return NULL;
  }
  else {
    //Shouldn't need to resize for null terminator because it was done just prior to this.
    *(line + lineLength) = '\0';
    return line;
  }
}