#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file infix.c
  @author Jeremiah Knizley
  This file performs base 10 or base 12 calculations in a given expression 
*/

/**
  parses an expression. Expressions can be a single number or a number raised to an exponent
  @return the expression in long form
*/
static long parse_exp()
{
  long value = parse_value();
  char next = skip_space();
  long exponent;
  if ( next == '^' ) {
    exponent = parse_value();
    value = exponential(value, exponent);
  }
  else {
    ungetc(next, stdin);
  }
  return value;

  
}
/**
  parses a sequence of multiplication or division operations between terms like 53 * 19 / 39
  Also works on a number with no operators
  @return the result of the operation.
*/
static long parse_mul_div()
{
  //default values for left and next, that way left doesn't change on the first iteration.
  long left = 1;
  char next = '*';
  // char temp = skip_space();
  // if (temp != '(') {
  //   ungetc(temp, stdin);
  // }
  while (next != '+' && next != '-' && next != EOF && next != '\n' && next != ')') {
    char temp = skip_space();
    if (temp == '(') {
      if (next == '*') {
        left = times(left, parse_mul_div());
      }
      else if (next == '/') {
        left = divide(left, parse_mul_div());
      }
    }
    else {
      ungetc(temp, stdin);
      long current = parse_exp();
      if (next == '*') {
        left = times(current, left);
      }
      else if (next == '/') {
        left = divide(left, current);
      }
      else {
        exit(FAIL_INPUT);
      }
    }
    next = (char) skip_space();
    // char trash = (char) skip_space();
    // ungetc(trash, stdin);
    
  }
  ungetc(next, stdin);

  return left;
}
/**
  Function responsible for handling much of the parenthesis operations. 
  Works similarly to parse_mul_div in that it goes until it finds a plus operator 
  that is not in a parenthesis.
  Works recursively if stacked parenthesis
  @return value found from parsing parenthesis terms
*/
long paren() {
  long left;
  left = parse_mul_div();
  long next;
  char operator = (char) skip_space();

  while (operator != ')') { 
    char temp = skip_space();
    if (temp == '(') {
      if (operator == '+') {
        left = plus(left, paren());
      }
      else if (operator == '-') {
        left = minus(left, paren());
      }
    }
    else {
      ungetc(temp, stdin);
      next = parse_mul_div();
      if (operator == '+') {
        left = plus(left, next);
      }
      else if (operator == '-') {
        left = minus(left, next);
      }
      else {
        exit(FAIL_INPUT);
      }
    }
    operator = (char) skip_space();
  }
  char newOperator = skip_space();
  if (newOperator == '*') {
    char temp = skip_space();
    if (temp == '(') {
      left = times(left, paren());
    }
    else {
      left = times(left, parse_mul_div());
    }
  }
  else if (newOperator == '/') {
    char temp = skip_space();
    if (temp == '(') {
      left = divide(left, paren());
    }
    else {
      left = divide(left, parse_mul_div());
    }
  }
  else {
    ungetc(newOperator, stdin);
  }
  return left;
}

/**
  the main part of the program. 
  Parses an expression written in base 10 or base 12 and prints a numerical answer
  ex. 10 * 10 * 10 in base 10 results in 1000, and EEE + 1 results in 1000 being printed
  @return int the exit status
*/
int main()
{
  long left;

  char temp = skip_space();
  if (temp == '(') {
    left = paren();
  }
  else {
    ungetc(temp, stdin);
    left = parse_mul_div();
  }
  long next;
  char operator = (char) skip_space();
  while (operator != EOF && operator != '\n') { 
    char temp = skip_space();
    if (temp == '(') {
      if (operator == '+') {
        left = plus(left, paren());
      }
      else if (operator == '-') {
        left = minus(left, paren());
      }
    }
    else {
      ungetc(temp, stdin);
      next = parse_mul_div();
      if (operator == '+') {
        left = plus(left, next);
      }
      else if (operator == '-') {
      left = minus(left, next);
      }
      else {
        exit(FAIL_INPUT);
      }
    }
    operator = (char) skip_space();
    while (operator == ')') {
      operator = skip_space();
    }
  }
  print_value(left);
  putchar('\n');
  return EXIT_SUCCESS;

}