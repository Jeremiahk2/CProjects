/**
  @file io.h
  @author Jeremiah Knizley
  header file for io.c. Contains some preprocessor macros and methods 
  that will be used in syntax.c and ident.c
  */

#include <stdio.h>
#include <stdbool.h>

/** Maximum length of an input line. */
#define LINE_LIMIT 100

/** Used for element of the output line in the default color. */
#define DEFAULT_COLOR 0

/** Used for element of the output line colored like that target identifier. */
#define IDENT_COLOR 1

/** For the extra credit, this is the color value for operators  */
#define OP_COLOR 2

int countLines(FILE *);

bool readLine(FILE *, char line[LINE_LIMIT + 1]);

void printLine(char line[LINE_LIMIT + 1], int color[LINE_LIMIT]);
