#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** The multiplier to increment a resizable line array by */
#define LINE_INC 2

/**
  @file input.h
  @author Jeremiah Knizley
  Header file for input.c. Contains all methods
*/

char *readLine(FILE *);
