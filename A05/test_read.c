/*----------------------------------------------
 * Author: 
 * Date: 
 * Tests read_ppm.c method.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int w, h;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // todo: print out the grid of pixels
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i * h + j];
      printf("(%d, %d, %d)", pixel.red, pixel.blue, pixel.green);
    }
  }
  free(pixels);
  return 0;
}

