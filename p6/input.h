#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
  @file input.h
  @author Jeremiah Knizley
  Header file for input.c. Contains all methods
*/

/** The multiplier to increment a resizable line array by */
#define LINE_INC 2

/**
  reads the next line from the input. 
  Afterwards, the fp paramater will have progressed past a newline character (if it didn't find EOF)
  @param fp the file to read a line from.
  @return a pointer to the array containing the line, or NULL if it found EOF instantly.
  */
char *readLine(FILE *);
