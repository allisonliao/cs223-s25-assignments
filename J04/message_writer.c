// J4 - Ally and Maryam

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data {
  float version;
  unsigned int year;
  unsigned int length;
};

int main(int argc, char** argv) {
  struct meta_data* metadata = malloc(sizeof(struct meta_data));
  metadata->version = 1;
  metadata->year = 2025;
  metadata->length = 11;
  char* message = malloc(12);
  strcpy(message, "hello world");

  char* filename = argv[1];
  FILE* output;
  output = fopen(filename, "wb");

  // add comment
  fprintf(output, "# Comment\n");
  int len = strlen(message);

  fwrite(metadata, sizeof(struct meta_data), 1, output);
  fwrite(message, 1, len + 1, output);

  free(metadata);
  free(message);
  fclose(output);
  return 0;
}
