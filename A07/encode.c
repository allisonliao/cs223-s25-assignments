/*----------------------------------------------
 * Author: Allison Liao
 * Date: 03/06/25
 * Reads PPM file, takes message, and encodes.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }

  // get pixels
  int w, h;
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  printf("Max number of characters in the image: %d\n", w * h * 3 / 8);
  printf("Enter a phrase:");
  char* phrase = malloc(w * h * 3 / 8);
  scanf(" %s", phrase);
  char* binphrase = malloc(w * h * 3);
  int ind = 0;
  char curr = phrase[0];
  char* binstr = malloc(strlen(phrase) * 8);

  for (int i = 0; i < strlen(phrase); i++) {
    curr = phrase[i];
    int c = curr;
    for (int a = 7; a >= 0; a--) {
      int rem = c % 2;
      // printf("c = %d; rem = %d; bin = %s\n", c, rem, binstr);
      binstr[i * 8 + a] = rem + '0';
      c >>= 1;
    }
  }
  //printf("binstr = %s", binstr);

  int idx = 0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      struct ppm_pixel *p = &pixels[i * h + j];
      p->red <<= 1; p->red >>= 1; p->red += (binstr[idx] - '0'); idx++;
      p->green <<= 1; p->green >>= 1; p->green += (binstr[idx] - '0'); idx++;
      p->blue <<= 1; p->blue >>= 1; p->blue += (binstr[idx] - '0'); idx++;
      //printf("pizel = %c, %c, %c", pixels[i * h + j].red, pixels[i * h + j].green)
    }
  }
  
  char* filename = malloc(strlen(argv[1]) + 8);
  strncpy(filename, argv[1], strlen(argv[1]) - 4);
  filename[strlen(argv[1]) - 4] = '\0';
  strcat(filename, "-encoded.ppm");
  printf("Writing file %s\n", filename);
  write_ppm(filename, pixels, w, h);

  free(phrase);
  free(binphrase);
  free(binstr);
  free(filename);
  return 0;
}

