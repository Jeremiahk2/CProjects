/**
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


void addSubkey(byte data[BLOCK_SIZE], byte const key[BLOCK_SIZE]);

void gFunction( byte dest[ WORD_SIZE ], byte const src[ WORD_SIZE ], int r );

void generateSubkeys(byte subkey[ROUNDS + 1][BLOCK_SIZE], byte const key[BLOCK_SIZE]);

void blockToSquare(byte square[BLOCK_ROWS][BLOCK_COLS], byte const data[BLOCK_SIZE]);

void squareToBlock(byte data[BLOCK_SIZE], byte const square[BLOCK_ROWS][BLOCK_COLS]);

void shiftRows(byte square[BLOCK_ROWS][BLOCK_COLS]);

void unShiftRows(byte square[BLOCK_ROWS][BLOCK_COLS]);

void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ] );

void encryptBlock(byte data[BLOCK_SIZE], byte key[BLOCK_SIZE]);

void decryptBlock(byte data[BLOCK_SIZE], byte key[BLOCK_SIZE]);

#endif
