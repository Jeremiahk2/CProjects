#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "number.h"
#include "operation.h"

/**
  @file infix.c
  @author Jeremiah Knizley
  This file performs base 10 or base 12 calculations in a given expression 
  In general, main handles addition and subtraction, parse_mul_div handles multiplication and division, 
  parse_exp handles numbers and exponents, and paren handles anything in parenthesis.
*/

/**
  parses an expression. Expressions can be a single number or a number raised to an exponent
  @return the expression in long form
*/
static long parse_exp()
{
  //get base value
  long value = parse_value();
  //get next value which might be an exponent
  char next = skip_space();
  long exponent;
  //check if next value is an exponent
  if ( next == '^' ) {
    exponent = parse_value();
    value = exponential(value, exponent);
  }
  else {
    ungetc(next, stdin); // if it's not we need to unget the character
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
  //default values for left and next, that way left doesn't change on the first iteration. (because it multiplied by 1)
  long left = 1;
  char next = '*';
  while (next != '+' && next != '-' && next != EOF && next != '\n' && next != ')') {
    //check for parentheses. This can be handled here because addition and subtraction aren't involved
    char temp = skip_space();
    if (temp == '(') {
      //recursively call parse_mul_div, this should end on a ).
      if (next == '*') {
        left = times(left, parse_mul_div());
      }
      else if (next == '/') {
        left = divide(left, parse_mul_div());
      }
    }
    //Normal operation without parentheses, parses the next expression and perform the operation
    else {
      //unget the character that could have been a parenthesis
      ungetc(temp, stdin);
      long current = parse_exp();
      if (next == '*') {
        left = times(current, left);
      }
      else if (next == '/') {
        left = divide(left, current);
      }
      else {
        //We had no open parenthesis, so if we get that or newline for next we exit unsuccessfully
        exit(FAIL_INPUT);
      }
    }
    //Next is at the end so that we can immediately check if we need to exit back to main
    next = (char) skip_space();
  }
  //next might be something important to main, like a plus or minus, so we unget it.
  ungetc(next, stdin);

  return left;
}
/**
  Function responsible for handling much of the parenthesis operations. 
  Works similarly to parse_mul_div in that it goes until it finds a plus operator 
  that is not in a parenthesis.
  Works recursively if stacked parenthesis (meaning 9+(8-(7-(6+5)))) or something like that.
  @return value found from parsing parenthesis terms
*/
long paren() {
  long left;
  //Main handled the open paren, so this gets the value of the first bit of multiplication and division after it.
  left = parse_mul_div();
  long next;
  //need to know the next operator (should be a plus or a minus)
  char operator = (char) skip_space();
  //We go until we reach the end of the parenthesis operations.
  while (operator != ')') { 
    char temp = skip_space();
    //if after the operator there is another parenthesis (which would be legal), we need to handle it
    if (temp == '(') {
      if (operator == '+') {
        //these are recursive calls to paren. If, this allows the code to handle
        //an infinite amount of input resembling 9 + (8 - (7 + (...
        left = plus(left, paren());
      }
      else if (operator == '-') {
        //same thing here
        left = minus(left, paren());
      }
    }
    else {
      //unget the char that might have been a parenthesis
      ungetc(temp, stdin);
      //proceed just like main would.
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
  //If the next operator is a multiplication, we can't exit to main after the parenthesis 
  if (newOperator == '*') {
    //so we parse through until we are back to being plus or minus, using recursive calls to paren or parse_mul_div
    char temp = skip_space();
    if (temp == '(') {
      left = times(left, paren());
    }
    else {
      left = times(left, parse_mul_div());
    }
  }
  else if (newOperator == '/') {
    //same thing here
    char temp = skip_space();
    if (temp == '(') {
      left = divide(left, paren());
    }
    else {
      left = divide(left, parse_mul_div());
    }
  }
  else {
    //If the operator wasn't a multiplication or division, we need to unget the character so main can handle it
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
  //Check for parenthesis, so paren can handle our initial value.
  //If the entire input consists of a sequeneces of parenthesis, this will never enter the while loop below.
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
    //check for parenthesis
    if (temp == '(') {
      if (operator == '+') {
        left = plus(left, paren());
      }
      else if (operator == '-') {
        left = minus(left, paren());
      }
    }
    else {
      //unget the potential parenthesis
      ungetc(temp, stdin);
      //proceed like normal, calling parse_mul_div and the appropriate operations.
      next = parse_mul_div();
      if (operator == '+') {
        left = plus(left, next);
      }
      else if (operator == '-') {
      left = minus(left, next);
      }
      else {
        //main only handles plus or minus operators, if anything else is there it should fail.
        exit(FAIL_INPUT);
      }
    }
    operator = (char) skip_space();
    //In the event that some part of the input ends with a sequence of closing parenthesis, this will clear them out.
    //These just tell us that the parenthesis is over, but paren already knows that so they can be gone.
    while (operator == ')') {
      operator = skip_space();
    }
  }
  print_value(left);
  putchar('\n');
  return EXIT_SUCCESS;

}
