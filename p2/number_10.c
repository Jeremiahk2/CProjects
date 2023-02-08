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
  //While \n doesn't equal end of file, for our purposes it means it's over, so returning EOF works.
  if (value == EOF || value == '\n') {
    return EOF;
  }
  //checks for negatives.
  bool negative = false;
  if (value == '-') {
    //there should be no space here because it's a negative value, so we use getchar
    //If it is a space, this will fail later when it exits to main. (because main will be expecting an operator)
    value = getchar() - CHAR0;
    //value is set to the negative of itself, because it's negative
    value = times(value, -1);
    negative = true;
  }
  else if (value >= '0' && value <= '9') {
    value = value - CHAR0;
  }
  else {
    //anything else here beyond a negative sign or a number should fail
    exit(FAIL_INPUT);
  }
  //this should be the second digit
  char next = skip_space();
  while (next >= '0' && next <= '9') {
    //base 10 conversion algorithm.
    value = times(value, BASE10);
    if (negative) {
      //if it's negative we need to minus it, to add on a negative digit properly.
      value = minus(value, (long)next - CHAR0);
    }
    else {
      value = plus(value, (long)next - CHAR0);
    }
    next = getchar();
  }
  //unget the next character (because it's probably an operator)
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
  //special case for 0 because on line 104 we test to see if the value is 0 for when we are out of digits
  if (val == 0) {
    putchar('0');
  }
  else {
    if (val < 0) {
      if (val != LONG_MIN) {
        putchar('-');
        //This function is recursive, so in order to prevent the dash from printing again, we change the value to be positive.
        val = times(val, -1);
      }
    }
    long digit;
    if (val == (LONG_MIN)) {
      //Special case for LONG_MIN, this makes the first digit negative, and on the next
      //recursive call, this won't run because now LONG_MIN is small enough to make positive.
      digit = times( -1, (val % BASE10));
    }
    else {
      digit = val % BASE10;
    }

    char newChar = (char) digit + CHAR0;

    val = divide(val, BASE10);
    //recursive is needed in order to print characters in the correct order.

    if (val != 0) {
      print_value(val);
    }
    //the prior if statement prints all values except ahead of the one parsed in THIS recursion instance, so now we print ours.
    putchar(newChar);
  }
}
