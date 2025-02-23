/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Tests read_ppm.c method.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main() {
  int w, h;
  char filename[64];
  strcpy(filename, "feep-raw.ppm");
  struct ppm_pixel* pixels = read_ppm(filename, &w, &h);

  // todo: print out the grid of pixels
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      printf("(%3d, %3d, %3d)", pixel.red, pixel.blue, pixel.green);
    }
    printf("\n");
  }

  free(pixels);
  return 0;
}

