#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
void sleep_ms(int milliseconds){
  Sleep(milliseconds);
}
#else
#include <unistd.h>
void sleep_ms(int milliseconds){
  usleep(milliseconds * 1000);
}
#endif

#include "rusalka.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

struct operation_parameters {
  char mode;
  char* key;
  char* text;
  struct unsigned_int_ptr number_sequence;
};

struct operation_parameters parse_args(int argc, char** argv){
  if(argc >= 4){
    struct operation_parameters op_params;
    // we can get the key first order of business.
    op_params.key = malloc(sizeof(char) * (strlen(argv[2])+1));
    strcpy(op_params.key, argv[2]);
    switch(argv[1][0]){
      case 'e': {
        printf("=== ENCRYPTION MODE >>>\n");
        op_params.mode = 'e';
        op_params.text = malloc(sizeof(char) * (strlen(argv[3])+1));
        strcpy(op_params.text, argv[3]);
        break;
      }
      case 'd': {
        printf("=== DECRYPTION MODE <<<\n");
        op_params.mode = 'd';
        int seq_count = argc - 3; // argc - prog_name - opmode - key
        op_params.number_sequence.size = seq_count;
        op_params.number_sequence.p = malloc(sizeof(unsigned int) * seq_count);
        for (int i = 3; i < argc; i++) {
          op_params.number_sequence.p[i - 3] = atoi(argv[i]);
        }
        break;
      }
      default: {
        fprintf(stderr, "Error: couldn't recognize opmode.\nUsage: %s <opmode: e|d> <key> <text>\n", argv[0]);
        exit(EXIT_FAILURE);
      }
      return op_params;
    }
  } else {
    fprintf(stderr,"Error: not enough args\nUsage: %s <opmode: e|d> <key> <text>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}

struct unsigned_int_ptr rus_encrypt(struct operation_parameters params){
  char* stripped_text = strip(params.text);
  char* stripped_key = strip(params.key);
  char* ciclic_key = generateKey(stripped_text, stripped_key);

  char* encrypted_text = cipherText(stripped_text, ciclic_key);
  struct unsigned_int_ptr seq = sequence(encrypted_text);

  free(stripped_text); free(stripped_key); free(ciclic_key);
  free(encrypted_text);
  return seq;
}

char* rus_decrypt(struct operation_parameters params){
  char* encrypted_text = desequence(params.number_sequence);
  char* stripped_key = strip(params.key);
  char* ciclic_key = generateKey(encrypted_text, stripped_key);

  char* decrypted_text = originalText(encrypted_text, ciclic_key);
  free(encrypted_text); free(stripped_key); free(ciclic_key);
  return decrypted_text;
}

int main(int argc, char** argv){
  struct operation_parameters params = parse_args(argc, argv);

  switch(params.mode){
    case 'e': {
      struct unsigned_int_ptr seq = rus_encrypt(params);
      printf("==== SUCCESS ====\n");
      printf("Sequence: ");
      fflush(stdout);
      for(int i = 0; i < seq.size; i++){
        printf("%d ",seq.p[i]);
        fflush(stdout);
        sleep_ms(50);
      }
      free(seq.p);
      putchar('\n');
      break;
    }
    case 'd': {
      char* decrypted_text = rus_decrypt(params);
      printf("==== SUCCESS ====\n");
      printf("Message: ");
      for(int i = 0; decrypted_text[i] != '\0'; i++){
        putchar(decrypted_text[i]);
        fflush(stdout);
        sleep_ms(50);
      } putchar('\n');
      free(decrypted_text); free(params.number_sequence.p);
      break;
    }
  }

  // BLAH BLAH BLAH
  exit(EXIT_SUCCESS);
}
