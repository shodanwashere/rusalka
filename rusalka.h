#ifndef RUSALKA_H
#define RUSALKA_H

struct unsigned_int_ptr{
  size_t size;
  unsigned int *p;
};

// Generates a Ciclic Key based on the text being encrypted/decrypted,
// where strlen(plaintext) == strlen(ciclicKey)
// The Generated Ciclic Key is malloc'd. If you don't need it anymore, free() it.
char* generateKey(char* plaintext, char* key);

// Encrypts plaintext using a supplied cyclicKey
// created with generateKey().
// Make sure plaintext has been stripped using strip()
// The cipherText is malloc'd. If you don't need it anymore, free() it.
char* cipherText(char* plaintext, char* cyclicKey);

// Decrypts an encrypted message using the supplied cyclicKey
// created with generateKey()
// Make sure this text has been stripped using strip()
// The original text is malloc'd. If you don't need it anymore, free() it.
char* originalText(char* cipherText, char* cyclicKey);

// Turns a piece of text into a Rusalka Number Sequence.
// Make sure your message has been encrypted beforehand
// with cipherText().
// The sequence in sequence.p is malloc'd. If you don't need it anymore, free() it.
struct unsigned_int_ptr sequence(char* text);

// Turns a number sequence into letters. Just a layer of obfuscation.
// The generated text should be decrypted using originalText()
// by supplying the original key.
// The generated text is malloc'd. If you don't need it anymore, free() it.
char* desequence(struct unsigned_int_ptr numberSequence);

// Strips a string of all whitespaces and special characters and
// turns all alphabetic characters into uppercase letters.
// The stripped text is malloc'd. If you don't need it anymore, free() it.
char* strip(char* text);

#endif
