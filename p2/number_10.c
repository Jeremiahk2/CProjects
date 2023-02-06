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
  char current = EOF;
  while (!charFound) {
    current = getchar();
    if ( current != ' ' ) {
      charFound = true;
    }
  }
  return (int)current;
}

long parse_value()
{
  long value = 0;
  value = skip_space();
  if (value == EOF || value == '\n') {
    return EOF;
  }
  bool negative = false;
  if (value == '-') {
    value = getchar() - 48;
    value = times(value, -1);
    negative = true;
  }
  else if (value >= '0' && value <= '9') {
    value = value - 48;
  }
  else {
    exit(102);
  }
  char next = skip_space();
  while (next >= '0' && next <= '9') {
    value = times(value, 10);
    if (negative) {
      value = minus(value, (long)next - 48);
    }
    else {
      value = plus(value, (long)next - 48);
    }
    next = getchar();
    // next = getchar();
  }
  ungetc( next, stdin );
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
      val = times(val, -1);
    }
    long digit = val % 10;

    char newChar = (char) digit + 48;

    val = divide(val, 10);
    if (val != 0) {
      print_value(val);
    }
    putchar(newChar);
  }
}