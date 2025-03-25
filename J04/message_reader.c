// J4 - Ally and Maryam

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data {
  float version;
  unsigned int year;
  unsigned int length;
};

int main(int argc, char **argv) {
  char *filename = argv[1];
  FILE *file;
  file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file. Exiting...");
    return 1;
  }

  char comment[64];

  fgets(comment, 64, file);
  printf("Comment: %s\n", comment);

  struct meta_data *metadata = malloc(sizeof(struct meta_data));

  // read float for version
  float *v = malloc(sizeof(float));
  fread(v, sizeof(*v), 1, file);
  metadata->version = *v;
  printf("Version: %f\n", metadata->version);

  // read year
  unsigned int *y = malloc(sizeof(int));
  fread(y, sizeof(*y), 1, file);
  metadata->year = *y;
  printf("Year: %u\n", metadata->year);

  // read length
  unsigned int *l = malloc(sizeof(int));
  fread(l, sizeof(*l), 1, file);
  metadata->length = *l;
  printf("Length: %u\n", metadata->length);

  char *data = malloc(*l + 1);
  int size = *l / 8;

  fread(data, *l, size, file);

  printf("Message: %s\n", data);

  free(v);
  free(y);
  free(l);
  free(data);
  free(metadata);
  fclose(file);

  return 0;
}
