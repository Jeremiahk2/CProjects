#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file number_10.c
  @author Jeremiah Knizley
  The number_10.c file is responsible for parsing and printing values in base 10
*/

/**
  Reads characters from standard input. 
  When it reaches a character that is not whitespace or EOF,
  it returns the code for that character and exits.
*/
int skip_space()
{
  bool charFound = false;
  while (!charFound) {
    char current = getchar();
    if ( current =! ' ' ) {
      charFound = true;
      return (int) current;
    }
  }
}

long parse_value()
{
  long value = 0;
  char next = getchar();
  bool negative = false;
  if (next == '-') {
    negative = true;
    next = getchar();
  }
  while (next >= '0' && next <= '9') {
    value = times(value, 10);
    value = plus(value, (long) next);
    next = getchar();
  }
  ungetc( next, stdin );
  if (negative) {
    return times(value, -1);
  }
  return value;
}

void print_value( long val )
{
  if (val == 0) {
    putchar('0');
    break;
  }
  if (val < 0) {
    putchar('-');
    times(val, -1);
  }
  long digit = val % 10;

  char newChar = (char) digit;

  val = divide(val, 10);
  if (val != 0) {
    putchar( print_value(val));
  }
  putchar(newChar);
}