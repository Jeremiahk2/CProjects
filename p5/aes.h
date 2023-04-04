/**
  @file aes.h
  @author Jeremiah Knizley
  File for handling encrypt and decrypt operations, as well as functions
  needed for handling those operations.
*/

#ifndef _AES_H_
#define _AES_H_

#include "field.h"

/** Number of bytes in an AES key or an AES block. */
#define BLOCK_SIZE 16

/** Numer of rows when a data block is arranged in a square. */
#define BLOCK_ROWS 4

/** Numer of columns when a data block is arranged in a square. */
#define BLOCK_COLS 4

/** Number of bytes in a word. */
#define WORD_SIZE 4

/** Number of roudns for 128-bit AES. */
#define ROUNDS 10

/**
  Adds the key to data using fieldAdd operations for each byte
  @param data the array that will hold the result of the operations
  @param key the array containing the key to add
*/
void addSubkey(byte data[BLOCK_SIZE], byte const key[BLOCK_SIZE]);

/**
  Performs the gfunction operation on src. The result is stored in dest
  @param dest the array containing the result of the operation
  @param src the array containing the initial word
  @param r the round that the gfunction is currently on.
*/
void gFunction( byte dest[ WORD_SIZE ], byte const src[ WORD_SIZE ], int r );

/**
  Generates ROUNDS + 1 subkeys, where the first index is just a copy of the key,
  and the rest are calculations using the number of rounds.
  @param subkey the location where the subkey should be stored
  @param key the key used to generate the subkeys
*/
void generateSubkeys(byte subkey[ROUNDS + 1][BLOCK_SIZE], byte const key[BLOCK_SIZE]);

/**
  Transforms a block of data into a 2d square of data.
  @param square a 4x4 square that contains the information in the data parameter
  @param data a 1d array containing the data that will be transformed into the square
*/
void blockToSquare(byte square[BLOCK_ROWS][BLOCK_COLS], byte const data[BLOCK_SIZE]);

/**
  Reverses the blockToSquare operation, transforming a 4x4 square of data into a 1d array of it.
  @param data the location where the square will be transformed into the 1d array
  @param square the initial location of the data contained in a 4x4 square
*/
void squareToBlock(byte data[BLOCK_SIZE], byte const square[BLOCK_ROWS][BLOCK_COLS]);

/**
  Shifts the rows of the squares by a certain amount. 
  Row 0 is not shifted,
  Row 1 is shifted 1 to the left
  Row 2 is shifted 2 to the left
  Row 3 is shifted 3 to the left
  @param square the location of the square, before and after
*/
void shiftRows(byte square[BLOCK_ROWS][BLOCK_COLS]);

/**
  Reverses the shiftRows operation.
  @param square the location of the square, before and after
*/
void unShiftRows(byte square[BLOCK_ROWS][BLOCK_COLS]);

/**
  Mixes the columns of the square array. This is done by using matrix multiplication with the following matrix:
  2 3 1 1
  1 2 3 1
  1 1 2 3
  3 1 1 2
  @param square the location of the data, before and after.
*/
void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/**
  Reverses the mixColumns operation (multiplied with an inverted matrix)
  @param square the location of the data, before and after
*/
void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/**
  Encrypts a block of data using the given key. 
  The order of operations are as follows:
  addSubkey
  repeat for 10 rounds:
  substitution function
  blockToSquare
  shiftRows
  mixColumns (not on round 10)
  squareToBlock
  addSubkey
  @param data the location where the encrypted data will be stored
  @param key the location of the key used for encryption
*/
void encryptBlock(byte data[BLOCK_SIZE], byte key[BLOCK_SIZE]);

/**
  Decrypts a block of data using the encrypt function in reverse order.
  @param data the location where the decrypted data will be stored
  @param key the key used for encryption
*/
void decryptBlock(byte data[BLOCK_SIZE], byte key[BLOCK_SIZE]);

#endif
