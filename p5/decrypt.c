#include "aes.h"
#include "field.h"
#include "io.h"

int main(int argc, char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "usage: encrypt <key-file> <input-file> <output-file>\n");
    exit(1);
  }
  int keySize = 0;
  byte *key = readBinaryFile(argv[1], &keySize);

  if (keySize != 16) {
    fprintf(stderr, "Bad key file: %s\n", argv[1]);
    exit(1);
  }

  int cipherSize = 0;
  byte *cipher = readBinaryFile(argv[2], &cipherSize);

  if (cipherSize == 0 || cipherSize % BLOCK_SIZE != 0) {
    fprintf(stderr, "Bad ciphertext file length: %s\n", argv[2]);
    exit(1);
  }

  for (int i = 0; i < cipherSize; i++) {
    byte block[BLOCK_SIZE];
    for (int j = 0; j < BLOCK_SIZE; j++) {
      block[j] = cipher[i * BLOCK_SIZE + j];
    }
    decryptBlock(block, key);
    for (int j = 0; j < BLOCK_SIZE; j++) {
      cipher[i * BLOCK_SIZE + j] = block[j];
    }
  }
  writeBinaryFile(argv[3], cipher, cipherSize);
}