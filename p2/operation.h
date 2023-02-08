/**
  @file operation.h
  @author Jeremiah Knizley
  Header file for operation.c, declares and describes methods and constants used for both
*/

/** minimum long value */
#define LONG_MIN (-9223372036854775807 - 1)
/** maximum long value */
#define LONG_MAX 9223372036854775807
/** exit code for mathematical overflow errors */
#define FAIL_OVERFLOW 100
/** exit code for dividing by zero */
#define FAIL_DIV0 103
/** exit code for invalid (negative) exponent */
#define FAIL_EXPONENT 101
/**
  Adds together a and b while detecting overflow
  @param a the number to be added with b
  @param b the number to be added with a
  @return long the result of the operation
*/
long plus(long, long);
/**
  Subtracts b from A while detecting overflow
  @param a the number that will subtract b from itself
  @param b the number to be subtracted from a
  @return long the result of the operation
*/
long minus(long, long);
/**
  Multiplies together a and b while detecting overflow
  @param a the number to be multiplied with b
  @param b the number to be multiplied with a
  @return long the result of the operation
*/
long times(long, long);
/**
  raises a to the power of b and returns the result while detecting overflow
  @param a the base number to be exponentiated
  @param b the exponent of a, must be positive
  @return long the result of the operation
*/
long exponential(long, long);
/**
  divides a by b and returns the result while detecting overflow
  @param a the number that will be divided by b
  @param b the number that divides a
  @return long the result of the operation
*/
long divide(long, long);
