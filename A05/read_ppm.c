/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *file;
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file. Exiting...");
    return NULL;
  }
  
  // parse header
  char buffer[255];
  fgets(buffer, sizeof(buffer), file);

  char *token;
  char delims[4] = {' ', '\t', '\n', '\r'};
  token = strtok(buffer, delims);
  char* header[4];

  for (int i = 0; token != 0; i++) {
    header[i] = token;
    token = strtok(NULL, delims);
  }

  // if (header[0] != "P6") {
  //   printf("PPM is not binary. Exiting...");
  //   return NULL;
  // }

  *w = atoi(header[1]);
  *h = atoi(header[2]);


  // account for single commented line, starting ith #

  struct ppm_pixel* output = malloc(sizeof(struct ppm_pixel) * *w * *h);
  if (output == NULL) {
    printf("Memory could not be allocated. Exiting...");
    return NULL;
  }
  char del[4] = {',', ' ', '(', ')'};
  for (int i = 0; i < *h; i++) {
    fgets(buffer, sizeof(buffer), file);
    for (int j = 0; j < *w; j++) {
      token = strtok(buffer, del);
      int red = atoi(token);
      token = strtok(buffer, del);
      int blue = atoi(token);
      token = strtok(buffer, del);
      int green = atoi(token);
      struct ppm_pixel pixel = {.red = red, .blue = blue, .green = green};
      output[i * *h + j] = pixel;
    }
  }


  fclose(file);
  return output;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
