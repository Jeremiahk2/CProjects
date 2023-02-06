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
  @return the integer value of the next character found.
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
/**
  parses the next value in the input using base 10 parsing.
  numbers must be on one line, negative numbers are accepted
  @return the value of the number parsed in base 10, I.E 1000 returns 1000
*/
long parse_value()
{
  long value = 0;
  value = skip_space();
  if (value == EOF || value == '\n') {
    return EOF;
  }
  bool negative = false;
  if (value == '-') {
    value = getchar() - CHAR0;
    value = times(value, -1);
    negative = true;
  }
  else if (value >= '0' && value <= '9') {
    value = value - CHAR0;
  }
  else {
    exit(FAIL_INPUT);
  }
  char next = skip_space();
  while (next >= '0' && next <= '9') {
    value = times(value, BASE10);
    if (negative) {
      value = minus(value, (long)next - CHAR0);
    }
    else {
      value = plus(value, (long)next - CHAR0);
    }
    next = getchar();
  }
  ungetc( next, stdin );
  return value;
}
/**
  prints a value written in base 10 into the output.
  Negative values are accepted
  @param val the value to be printed into the output. 
*/
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
    long digit = val % BASE10;

    char newChar = (char) digit + CHAR0;

    val = divide(val, BASE10);
    if (val != 0) {
      print_value(val);
    }
    putchar(newChar);
  }
}