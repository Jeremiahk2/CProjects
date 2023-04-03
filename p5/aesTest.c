/**
  @file aesTest.c
  @author Sturgill
  Unit test program for the AES component.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aes.h"

/** Number of tests we should have, if they're all turned on. */
#define EXPECTED_TOTAL 38

/** Total number or tests we tried. */
static int totalTests = 0;

/** Number of test cases passed. */
static int passedTests = 0;

/** Macro to check the condition on a test case, keep counts of
    passed/failed tests and report a message if the test fails. */
#define TestCase( conditional ) {\
  totalTests += 1; \
  if ( conditional ) { \
    passedTests += 1; \
  } else { \
    printf( "**** Failed unit test on line %d of %s\n", __LINE__, __FILE__ );    \
  } \
}

int main()
{
  // As you finish parts of your implementation, move this directive
  // down past the blocks of code below.  That will enable tests of
  // various functions you're expected to implement.
  
// #ifdef DISABLE_TESTS
    
  ////////////////////////////////////////////////////////////////////////
  // Test gFunction()
  
  {
    // Random, 4-byte value.
    byte src[ WORD_SIZE ] = { 0x18, 0x15, 0x7D, 0x6B };

    // Run the g function, round 1.
    byte dest[ WORD_SIZE ];
    gFunction( dest, src, 1 );

    // Make sure we got the right results.
    byte expected[ WORD_SIZE ] = { 0x58, 0xFF, 0x7F, 0xAD };
    TestCase( memcmp( dest, expected, WORD_SIZE ) == 0 );
  }
// #ifdef DISABLE_TESTS 
  // Another gFunction test.

  {
    // Random, 4-byte value.
    byte src[ WORD_SIZE ] = { 0x7E, 0x9E, 0xDE, 0x09 };

    // Run the g function, round 2.
    byte dest[ WORD_SIZE ];
    gFunction( dest, src, 2 );

    // Make sure we got the right results.
    byte expected[ WORD_SIZE ] = { 0x09, 0x1D, 0x01, 0xF3 };
    TestCase( memcmp( dest, expected, WORD_SIZE ) == 0 );
  }
  // #ifdef DISABLE_TESTS 
  // One more gFunction test.

  {
    // Random, 4-byte value.
    byte src[ WORD_SIZE ] = { 0x3D, 0x39, 0x33, 0x50 };

    // Run the g function, round 10.
    byte dest[ WORD_SIZE ];
    gFunction( dest, src, 10 );

    // Make sure we got the right results.
    byte expected[ WORD_SIZE ] = { 0x24, 0xC3, 0x53, 0x27 };
    TestCase( memcmp( dest, expected, WORD_SIZE ) == 0 );
  }
  // #ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test generateSubkeys();
  
  {
    // Random, 16-byte key.
    byte key[ BLOCK_SIZE ] = {
      0xF7, 0x26, 0x4C, 0xC8, 0xDF, 0x90, 0xF1, 0xCA,
      0xEE, 0x7A, 0xE1, 0x99, 0x11, 0xF7, 0x6B, 0xD1 };

    // Generate all the subkeys based on this key.
    byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ];
    generateSubkeys( subkey, key );

    // Make sure we got all the right subkeys.
    byte expected[ ROUNDS + 1 ][ BLOCK_SIZE ] = {
      { 0xF7, 0x26, 0x4C, 0xC8, 0xDF, 0x90, 0xF1, 0xCA,
        0xEE, 0x7A, 0xE1, 0x99, 0x11, 0xF7, 0x6B, 0xD1 },
      { 0x9E, 0x59, 0x72, 0x4A, 0x41, 0xC9, 0x83, 0x80,
        0xAF, 0xB3, 0x62, 0x19, 0xBE, 0x44, 0x09, 0xC8 },
      { 0x87, 0x58, 0x9A, 0xE4, 0xC6, 0x91, 0x19, 0x64,
        0x69, 0x22, 0x7B, 0x7D, 0xD7, 0x66, 0x72, 0xB5 },
      { 0xB0, 0x18, 0x4F, 0xEA, 0x76, 0x89, 0x56, 0x8E,
        0x1F, 0xAB, 0x2D, 0xF3, 0xC8, 0xCD, 0x5F, 0x46 },
      { 0x05, 0xD7, 0x15, 0x02, 0x73, 0x5E, 0x43, 0x8C,
        0x6C, 0xF5, 0x6E, 0x7F, 0xA4, 0x38, 0x31, 0x39 },
      { 0x12, 0x10, 0x07, 0x4B, 0x61, 0x4E, 0x44, 0xC7,
        0x0D, 0xBB, 0x2A, 0xB8, 0xA9, 0x83, 0x1B, 0x81 },
      { 0xDE, 0xBF, 0x0B, 0x98, 0xBF, 0xF1, 0x4F, 0x5F,
        0xB2, 0x4A, 0x65, 0xE7, 0x1B, 0xC9, 0x7E, 0x66 },
      { 0x43, 0x4C, 0x38, 0x37, 0xFC, 0xBD, 0x77, 0x68,
        0x4E, 0xF7, 0x12, 0x8F, 0x55, 0x3E, 0x6C, 0xE9 },
      { 0x71, 0x1C, 0x26, 0xCB, 0x8D, 0xA1, 0x51, 0xA3,
        0xC3, 0x56, 0x43, 0x2C, 0x96, 0x68, 0x2F, 0xC5 },
      { 0x2F, 0x09, 0x80, 0x5B, 0xA2, 0xA8, 0xD1, 0xF8,
        0x61, 0xFE, 0x92, 0xD4, 0xF7, 0x96, 0xBD, 0x11 },
      { 0x89, 0x73, 0x02, 0x33, 0x2B, 0xDB, 0xD3, 0xCB,
        0x4A, 0x25, 0x41, 0x1F, 0xBD, 0xB3, 0xFC, 0x0E }
    };
    
    for ( int r = 0; r <= ROUNDS; r++ ) {
      TestCase( memcmp( subkey[ r ], expected[ r ], BLOCK_SIZE ) == 0 );
    }
  }
  ////////////////////////////////////////////////////////////////////////
  // Test addSubkey()
  
  {
    // Block of 16 random values
    byte data[ BLOCK_SIZE ] = {
      0x9B, 0x38, 0x8C, 0x9D, 0xCA, 0xA6, 0x2C, 0xBF,
      0xFC, 0xF3, 0x0A, 0xD4, 0xFC, 0xBA, 0xAA, 0xD6 };

    // Subkey of 16 random values
    byte subkey[ BLOCK_SIZE ] = {
      0xB0, 0xE7, 0xB0, 0x89, 0x1E, 0x9B, 0x25, 0x83,
      0x4F, 0x6F, 0xC9, 0xBE, 0x39, 0x73, 0xAA, 0x49 };

    // Add the block and the subkey.
    addSubkey( data, subkey );

    // Make sure we got the right results.
    byte expected[ BLOCK_SIZE ] = {
      0x2B, 0xDF, 0x3C, 0x14, 0xD4, 0x3D, 0x09, 0x3C,
      0xB3, 0x9C, 0xC3, 0x6A, 0xC5, 0xC9, 0x00, 0x9F };
    TestCase( memcmp( data, expected, BLOCK_SIZE ) == 0 );
  }
// #ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test blockToSquare()
  
  {
    // Block of 16-different values.
    byte block[ BLOCK_SIZE ] = {
      0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
      0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };

    // Convert 1D block to 2d, square arrangement.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ];
    blockToSquare( square, block );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0x1, 0x5, 0x9, 0xD },
      { 0x2, 0x6, 0xA, 0xE }, { 0x3, 0x7, 0xB, 0xF } };
    
    for ( int r = 0; r < BLOCK_ROWS; r++ )
      TestCase( memcmp( square[ r ], expected[ r ], BLOCK_COLS ) == 0 );
  }
  // #ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test squareToBlock()
  
  {
    // Square of 16 different values.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0x1, 0x5, 0x9, 0xD },
      { 0x2, 0x6, 0xA, 0xE }, { 0x3, 0x7, 0xB, 0xF } };
    
    // Convert 1D block to 2d, square arrangement.
    byte block[ BLOCK_SIZE ];
    squareToBlock( block, square );

    // make sure we got the correct 1D block result.
    byte expected[ BLOCK_SIZE ] = {
      0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
      0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
    
    TestCase( memcmp( block, expected, BLOCK_SIZE ) == 0 );
  }
  // #ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test shiftRows()
  
  {
    // Square of 16 different values.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0x1, 0x5, 0x9, 0xD },
      { 0x2, 0x6, 0xA, 0xE }, { 0x3, 0x7, 0xB, 0xF } };
    
    shiftRows( square );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0x5, 0x9, 0xD, 0x1 },
      { 0xA, 0xE, 0x2, 0x6 }, { 0xF, 0x3, 0x7, 0xB } };
    
    for ( int r = 0; r < BLOCK_ROWS; r++ )
      TestCase( memcmp( square[ r ], expected[ r ], BLOCK_COLS ) == 0 );
  }
  // #ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test unShiftRows()
  
  {
    // Square of 16 different values.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0x1, 0x5, 0x9, 0xD },
      { 0x2, 0x6, 0xA, 0xE }, { 0x3, 0x7, 0xB, 0xF } };
    
    unShiftRows( square );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x0, 0x4, 0x8, 0xC }, { 0xD, 0x1, 0x5, 0x9 },
      { 0xA, 0xE, 0x2, 0x6 }, { 0x7, 0xB, 0xF, 0x3 } };
    
    for ( int r = 0; r < BLOCK_ROWS; r++ )
      TestCase( memcmp( square[ r ], expected[ r ], BLOCK_COLS ) == 0 );
  }
#ifdef DISABLE_TESTS 
  ////////////////////////////////////////////////////////////////////////
  // Test mixColumns()
  
  {
    // Square of 16 random values.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0xD6, 0x6D, 0xEA, 0xB7 }, { 0xF8, 0x3C, 0x7A, 0x8B },
      { 0x3D, 0xE5, 0x13, 0x46 }, { 0xB6, 0x0B, 0x8D, 0x1A } };
    
    mixColumns( square );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x2F, 0x70, 0xDF, 0xAF }, { 0xCC, 0x2A, 0xA6, 0x6A },
      { 0x95, 0x9D, 0x3A, 0x9E }, { 0xD3, 0x78, 0x4D, 0x3B } };
    
    for ( int r = 0; r < BLOCK_ROWS; r++ )
      TestCase( memcmp( square[ r ], expected[ r ], BLOCK_COLS ) == 0 );
  }

  ////////////////////////////////////////////////////////////////////////
  // Test unMixColumns()
  
  {
    // Square of 16 random values.
    byte square[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x20, 0x59, 0xC0, 0x77 }, { 0x5D, 0x04, 0xEF, 0xFE },
      { 0x4B, 0xC6, 0x36, 0x17 }, { 0x83, 0xE2, 0x23, 0x50 } };
    
    unMixColumns( square );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_ROWS ][ BLOCK_COLS ] = {
      { 0x07, 0x35, 0x9A, 0x01 }, { 0x4E, 0xB2, 0xAA, 0x5D },
      { 0x1D, 0x58, 0x18, 0xE6 }, { 0xE1, 0xA6, 0x12, 0x74 } };

    for ( int r = 0; r < BLOCK_ROWS; r++ )
      TestCase( memcmp( square[ r ], expected[ r ], BLOCK_COLS ) == 0 );
  }

  ////////////////////////////////////////////////////////////////////////
  // Test encryptBlock()
  
  {
    // Random block of bytes.
    byte data[ BLOCK_SIZE ] = {
      0x04, 0x52, 0xAA, 0x23, 0x71, 0xA7, 0xBF, 0xDB,
      0x80, 0x01, 0xC5, 0x5D, 0xB4, 0x1F, 0x70, 0x82 };
    
    // Random key.
    byte key[ BLOCK_SIZE ] = {
      0x34, 0x27, 0x15, 0xA1, 0xDB, 0xF3, 0x3C, 0x72,
      0x09, 0xBA, 0x87, 0x7D, 0xC2, 0x1F, 0x73, 0x1A };
    
    encryptBlock( data, key );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_SIZE ] = {
      0xFE, 0x4E, 0x2A, 0x42, 0xC9, 0x3F, 0xCF, 0xF1,
      0x89, 0x9D, 0xC1, 0xB6, 0xA4, 0x53, 0x47, 0xFF };

    TestCase( memcmp( data, expected, BLOCK_SIZE ) == 0 );
  }

  ////////////////////////////////////////////////////////////////////////
  // Test decryptBlock()
  
  {
    // Random block of bytes.
    byte data[ BLOCK_SIZE ] = {
      0xDE, 0xE9, 0x57, 0x0E, 0x94, 0x0B, 0xE0, 0xB2,
      0x7B, 0x45, 0x82, 0x2C, 0xAA, 0x38, 0xA4, 0x7E };
    
    // Random key.
    byte key[ BLOCK_SIZE ] = {
      0x5A, 0xC3, 0xFC, 0xC3, 0x4C, 0xD4, 0x60, 0xD7,
      0xFE, 0x9B, 0x66, 0x83, 0xC7, 0xDC, 0xDE, 0x30 };
    
    decryptBlock( data, key );

    // Make sure we got the right results for each row.
    byte expected[ BLOCK_SIZE ] = {
      0x12, 0x83, 0xE6, 0xB3, 0xA1, 0xA9, 0xFA, 0xC0,
      0xCE, 0xFC, 0x08, 0x87, 0xDE, 0x96, 0x06, 0xC1 };

    TestCase( memcmp( data, expected, BLOCK_SIZE ) == 0 );
  }

  // Once you move the #ifdef DISABLE_TESTS to here, you've enabled
  // all the tests.

#endif

  // Report a message if some tests are still disabled.
  if ( totalTests < EXPECTED_TOTAL )
    printf( "** %d of %d tests currently enabled.\n", totalTests,
            EXPECTED_TOTAL );
    
  // Exit successfully if all tests are enabled and they all pass.
  if ( passedTests != EXPECTED_TOTAL )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}
