#ifndef RUSALKA_H
#define RUSALKA_H

struct unsigned_int_ptr{
  size_t size;
  unsigned int *p;
};

// Generates a Ciclic Key based on the text being encrypted/decrypted, where strlen(plaintext) == strlen(ciclicKey)
char* generateKey(char* plaintext, char* key);

// Encrypts plaintext using a supplied cyclicKey
// created with generateKey().
// Make sure plaintext has been stripped using strip()
char* cipherText(char* plaintext, char* cyclicKey);

// Decrypts an encrypted message using the supplied cyclicKey
// created with generateKey()
// Make sure this text has been stripped using strip()
char* originalText(char* cipherText, char* cyclicKey);

// Turns a piece of text into a Rusalka Number Sequence.
// Make sure your message has been encrypted beforehand
// with cipherText().
struct unsigned_int_ptr sequence(char* text);

// Turns a number sequence into letters. Just a layer of obfuscation.
// The generated text should be decrypted using originalText()
// by supplying the original key.
char* desequence(struct unsigned_int_ptr numberSequence);

// Strips a string of all whitespaces and special characters and
// turns all alphabetic characters into uppercase letters.
char* strip(char* text);

#endif
