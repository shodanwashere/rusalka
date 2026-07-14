#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct unsigned_int_ptr{
  size_t size;
  unsigned int *p;
};

char* generateKey(char* plaintext, char* key){
  int x = strlen(plaintext);
  char* newKey = (char*) malloc(sizeof(char) * x);
  for (int i = 0, j = 0; j < x; i++, j++) {
    if (x == i)
      i = 0;
    newKey[j] = key[j];
  }
  return newKey;
}

char* cipherText(char* plaintext, char* cyclicKey){
  int x = strlen(plaintext);
  char* cipherText = (char*) malloc(sizeof(char) * x);
  for (int i = 0; i < x; i++){
    char z = (plaintext[i] + cyclicKey[i]) % 26;
    z += 'A';
    cipherText[i] = z;
  }
  return cipherText;
}

char* originalText(char* cipherText, char* cyclicKey){
  int x = strlen(cipherText);
  char* plaintext = (char*) malloc(sizeof(char) * x);
  for(int i = 0; i < x; i++){
    char z = (cipherText[i] - cyclicKey[i] + 26) % 26;
    z += 'A';
    plaintext[i] = z;
  }
  return plaintext;
}

struct unsigned_int_ptr sequence(char* text){
  int x = strlen(text);
  struct unsigned_int_ptr numberSequence;
  numberSequence.p = (unsigned int*) malloc(sizeof(unsigned int) * x);
  numberSequence.size = (sizeof(unsigned int) * x);
  for(int i = 0; i < x; i++){
    unsigned int z = (unsigned int) text[i] - 65; // 65 = 'A' in ASCII table
    numberSequence.p[i] = z;
  }
  return numberSequence;
}

char* desequence(struct unsigned_int_ptr numberSequence){
  int x = numberSequence.size/sizeof(unsigned int);
  char* cipherText = (char*) malloc(sizeof(char) * x);
  for(int i = 0; i < x; i++){
    char z = ((char) numberSequence.p[i]) + 65;
    cipherText[i] = z;
  }
  return cipherText;
}

char* strip(char* text){
  // unfortunately uses more memory than needed but whatever
  int x = strlen(text);
  char* strippedText = (char*) malloc(sizeof(char) * x);
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

int main(){
  char key[] = "It is strange and striking that climate change activists have not commited any acts of terrorism.";
  char text[] = "Proceed with plan as usual. Do not hesitate.";

  printf("=== STRIPPING TEXT ===\n");
  char* strippedKey = strip(key);
  char* strippedText = strip(text);
  printf("> Stripped Key: %s\n",strippedKey);
  printf("> Stripped Text: %s\n",strippedText);

  printf("=== CYCLING KEY ===\n");
  char* cyclicKey = generateKey(strippedText, strippedKey);
  free(strippedKey);
  
  printf("=== CIPHERING TEXT ===\n");
  char* encrypted = cipherText(strippedText, cyclicKey);
  printf("> Original Text: %s\n", strippedText);
  printf("> Encrypted    : %s\n", encrypted);

  printf("=== GENERATING NUMBER SEQUENCE ===\n");
  struct unsigned_int_ptr numberSequence = sequence(encrypted);

  printf("==================================\n");
  printf("ORIGINAL MESSAGE: \"%s\"\n", text);
  printf("NUMBER SEQUENCE : ");
  for(int i = 0; i < numberSequence.size/sizeof(unsigned int); i++){
    printf("%d ", numberSequence.p[i]);
  }
  printf("\n");
  return 0;
}
