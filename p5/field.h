/**
  @file field.h
  @author Jeremiah Knizley
  Headerfile for field.c
  Contains all methods and standard libraries needed.
*/

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdlib.h>
#include <stdio.h>

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8
/** The amount to shift the mask by in binary */
#define MASK_SHIFT 2
/** The preset value for the reducer for binary multiplication */
#define REDUCER 0x11B

/**
  Function for adding byte a to byte b
  This method expectes both paramaters to be 8-bit Galois fields used by AES
  @param a the byte to be added with b
  @param b the byte to be added with a
  @return the result of the adding operation.
*/
byte fieldAdd(byte a, byte b);

/**
  Function for subtracting two values.
  This method functions exactly like fieldAdd, 
  and expects both paramaters to be 8-bit Galois fields used by AES
  @param a the byte to be subtracted with b
  @param b the byte to be subtracted with a
  @return the result of the subtraction operation.
*/
byte fieldSub(byte a, byte b);

/**
  Multiplied a with b
  Both parameters are expected to be 8-bit Galois fields used by AES
  The result will fit into a byte 
  @param a the byte to be multiplied with b
  @param b the byte to be multiplied with a
  @return the result of the operation
*/
byte fieldMul(byte a, byte b);

#endif
