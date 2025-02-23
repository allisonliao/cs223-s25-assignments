/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Displays PPM file as ascii art.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char *argv[]) {
  int w, h;
  // get pixels
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);

  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  char ascii[11] = "@#\%*o;:,. ";
  ascii[10] = ' ';

  // print
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      struct ppm_pixel pixel = pixels[i*w + j];
      float intensity = 1.0/3.0 * (pixel.red + pixel.green + pixel.blue);
      int idx = floor(intensity/25.5);
      printf("%c", ascii[idx]);
    }
    printf("\n");
  }
  free(pixels);
  return 0;
}
