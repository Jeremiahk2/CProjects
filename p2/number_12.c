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
  parses the next value in the input using base 12 parsing.
  numbers must be on one line, negative numbers are accepted
  @return the value of the number parsed in base 12, ex. EEE = 1727
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
    value = getchar();
    if (value == 'E') {
      value = E;
    }
    else if (value == 'X') {
      value = X;
    }
    else if (value >= '0' && value <= '9') {
      value = minus(value, CHAR0);
    }
    value = times(value, -1);
    negative = true;
  }
  else if ((value >= '0' && value <= '9') || value == 'E' || value == 'X') {
    if (value == 'E') {
      value = E;
    }
    else if (value == 'X') {
      value = X;
    }
    else {
      value = minus(value, CHAR0);
    }
  }
  else {
    exit(FAIL_INPUT);
  }
  char next = skip_space();
  long numNext = 0;
  while ((next >= '0' && next <= '9') || next == 'E' || next == 'X') {
    if (next == 'E') {
      numNext = E;
    }
    else if (next == 'X') {
      numNext = X;
    }
    else {
      numNext = minus(next, CHAR0);
    }
    value = times(value, BASE12);
    if (negative) {
      value = minus(value, numNext);
    }
    else {
      value = plus(value, numNext);
    }
    next = getchar();
    // next = getchar();
  }
  ungetc( next, stdin );
  return value;
}

/**
  prints a value written in base 12 into the output.
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
      if (val != LONG_MIN) {
      putchar('-');
      val = times(val, -1);
      }
    }
    long digit;
    if (val == (LONG_MIN)) {
      digit = times( -1, (val % BASE12));
    }
    else {
      digit = val % BASE12;
    }

    char newChar;
    if (digit == X) {
      newChar = 'X';
    }
    else if (digit == E) {
      newChar = 'E';
    }
    else {
      newChar = (char)plus(digit, CHAR0);
    }
    val = divide(val, BASE12);
    if (val != 0) {
      print_value(val);
    }
    putchar(newChar);
  }
}