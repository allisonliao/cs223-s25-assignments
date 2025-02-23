/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Method to read a PPM file and store as object.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *file;
  file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error opening file. Exiting...");
    return NULL;
  }

  // parse header
  char *header[2];

  char buffer[255];
  fgets(buffer, sizeof(buffer), file);

  // account for single commented line, starting with #
  fgets(buffer, sizeof(buffer), file);
  fgets(buffer, sizeof(buffer), file);

  header[0] = strtok(buffer, " ");
  header[1] = strtok(NULL, " ");

  *w = atoi(header[0]);
  *h = atoi(header[1]);

  fgets(buffer, sizeof(buffer), file);

  struct ppm_pixel* output = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));
  if (!output) {
    printf("Memory could not be allocated. Exiting...");
    return NULL;
  }

  fread(output, sizeof(struct ppm_pixel), (*w) * (*h), file);
  
  fclose(file);
  return output;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
