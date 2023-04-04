/**
  @file decrypt.c
  @author Jeremiah Knizley
  File for decrypting data from a file.
  usage: ./decrypt <key-file> <cipher-file> <output-file>
*/

#include "aes.h"
#include "field.h"
#include "io.h"

/** the number of arguments the program should have */
#define NUM_ARGS 4
/** The index in argv where the key file name should be */
#define KEY_FILE 1
/** The index in argv where the cipher file name should be */
#define CIPHER_FILE 2
/** The index in argv where the output file name should be */
#define OUTPUT_FILE 3

/**
  Main part of the program. decrypts the cipher file using the given key.
  File must contain a multiple of 16 bytes.
  @param argc the number of command-line arguments. Should be 4 to be valid.
  @param argv the array containing the command-line arguments.
  @return exit status
*/
int main(int argc, char *argv[])
{
  if (argc != NUM_ARGS) {
    fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }
  int keySize = 0;
  byte *key = readBinaryFile(argv[KEY_FILE], &keySize);
  if (key == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[KEY_FILE]);
    free(key);
    exit(1);
  }

  if (keySize != BLOCK_SIZE) {
    fprintf(stderr, "Bad key file: %s\n", argv[KEY_FILE]);
    free(key);
    exit(1);
  }

  int cipherSize = 0;
  byte *cipher = readBinaryFile(argv[CIPHER_FILE], &cipherSize);
  if (cipher == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[CIPHER_FILE]);
    free(cipher);
    free(key);
    exit(1);
  }

  if (cipherSize == 0 || cipherSize % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad ciphertext file length: %s\n", argv[CIPHER_FILE]);
    free(key);
    free(cipher);
    exit(1);
  }

  for (int i = 0; i < cipherSize / BLOCK_SIZE; i++) {
    byte block[BLOCK_SIZE];
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block[j] = cipher[i * BLOCK_SIZE + j];
    }
    decryptBlock(block, key);
    for (int j = 0; j < BLOCK_SIZE; j++) {
      cipher[i * BLOCK_SIZE + j] = block[j];
    }
  }
  writeBinaryFile(argv[OUTPUT_FILE], cipher, cipherSize);

  free(cipher);
  free(key);

  return EXIT_SUCCESS;
}
