#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rusalka.h"

char* generateKey(char* plaintext, char* key){
  int x = strlen(plaintext);
  char* newKey = (char*) malloc(sizeof(char) * (x+1));
  int i, j;
  for (i = 0, j = 0; j < x; i++, j++) {
    if (x == i)
      i = 0;
    newKey[j] = key[j];
  }
  newKey[j] = '\0';
  return newKey;
}

char* cipherText(char* plaintext, char* cyclicKey){
  int x = strlen(plaintext);
  char* cipherText = (char*) malloc(sizeof(char) * (x+1));
  int i;
  for (i = 0; i < x; i++){
    char z = (plaintext[i] + cyclicKey[i]) % 26;
    z += 'A';
    cipherText[i] = z;
  }
  cipherText[i] = '\0';
  return cipherText;
}

char* originalText(char* cipherText, char* cyclicKey){
  int x = strlen(cipherText);
  char* plaintext = (char*) malloc(sizeof(char) * (x+1));
  int i;
  for(i = 0; i < x; i++){
    char z = (cipherText[i] - cyclicKey[i] + 26) % 26;
    z += 'A';
    plaintext[i] = z;
  }
  plaintext[i] = '\0';
  return plaintext;
}

struct unsigned_int_ptr sequence(char* text){
  int x = strlen(text);
  struct unsigned_int_ptr numberSequence;
  numberSequence.p = (unsigned int*) malloc(sizeof(unsigned int) * x);
  numberSequence.size = (x);
  for(int i = 0; i < x; i++){
    if(text[i] == '\0') break;
    unsigned int z = (unsigned int) text[i] - 65; // 65 = 'A' in ASCII table
    numberSequence.p[i] = z;
  }
  return numberSequence;
}

char* desequence(struct unsigned_int_ptr numberSequence){
  int x = numberSequence.size;
  char* cipherText = (char*) malloc(sizeof(char) * (x+1));
  int i;
  for(i = 0; i < x; i++){
    char z = ((char) numberSequence.p[i]) + 65;
    cipherText[i] = z;
  }
  cipherText[i] = '\0';
  return cipherText;
}

char* strip(char* text){
  // unfortunately uses more memory than needed but whatever
  int x = strlen(text);
  char* strippedText = (char*) malloc(sizeof(char) * (x+1));
  int c = 0;
  for(int i = 0; i < x; i++){
    if(isalnum(text[i])){
      strippedText[c] = toupper(text[i]);
      c++;
    }
  }
  strippedText[c] = '\0';
  return strippedText;
}
