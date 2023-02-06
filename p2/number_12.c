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
    value = getchar();
    if (value == 'E') {
      value = 11;
    }
    else if (value == 'X') {
      value = 10;
    }
    else if (value >= '0' && value <= '9') {
      value = minus(value, 48);
    }
    value = times(value, -1);
    negative = true;
  }
  else if ((value >= '0' && value <= '9') || value == 'E' || value == 'X') {
    if (value == 'E') {
      value = 11;
    }
    else if (value == 'X') {
      value = 10;
    }
    else {
      value = minus(value, 48);
    }
  }
  else {
    exit(102);
  }
  char next = skip_space();
  long numNext = 0;
  while ((next >= '0' && next <= '9') || next == 'E' || next == 'X') {
    if (next == 'E') {
      numNext = 11;
    }
    else if (next == 'X') {
      numNext = 10;
    }
    else {
      numNext = minus(next, 48);
    }
    value = times(value, 12);
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
      digit = times( -1, (val % 12));
    }
    else {
      digit = val % 12;
    }

    // char newChar = (char) digit + 48;
    char newChar;
    if (digit == 10) {
      newChar = 'X';
    }
    else if (digit == 11) {
      newChar = 'E';
    }
    else {
      newChar = (char)plus(digit, 48);
    }
    val = divide(val, 12);
    if (val != 0) {
      print_value(val);
    }
    putchar(newChar);
  }
}