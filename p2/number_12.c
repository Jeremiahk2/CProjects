#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file number_12.c
  @author Jeremiah Knizley
  The number_12.c file is responsible for parsing and printing values in base 12
*/

/**
  Reads characters from standard input. 
  When it reaches a character that is not whitespace or EOF,
  it returns the code for that character and exits.
*/
int skip_space()
{
  bool charFound = false;
  char current = EOF;
  while (!charFound) {
    char current = getchar();
    if ( current != ' ' ) {
      charFound = true;
    }
  }
  return (int)current;
}

long parse_value()
{
  long value = 0;
  char next = getchar();

  while ((next >= '0' && next <= '9') || next == 'E' || next == 'X') {
    value = times(value, 12);
    value = plus(value, (long) next);
    next = getchar();
    ungetc( next, stdin );
  }
  return value;
}

void print_value( long val )
{
  if (val == 0) {
    putchar('0');
  }
  else {
    if (val < 0) {
    putchar('-');
    times(val, -1);
  }
  long digit = val % 12;

  char newChar = (char) digit;
  if (digit == 10) {
    newChar = 'X';
  }
  else if (digit == 11) {
    newChar = 'E';
  }

  val = divide(val, 12);
  if (val != 0) {
    print_value(val);
  }
  putchar(newChar);
  }
}