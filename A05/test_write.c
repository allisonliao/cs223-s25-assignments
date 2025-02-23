/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Tests write_ppm.c method.
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  int w, h;
  w = h = 4;
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // test writing the file to test.ppm, reload it, and print the contents
  write_ppm("test.ppm", pixels, w, h);
  struct ppm_pixel* reloaded = read_ppm("test.ppm", &w, &h);

  printf("Testing file feep-raw.ppm: %d %d\n", w, h);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      struct ppm_pixel pixel = pixels[i * w + j];
      printf("(%3d, %3d, %3d)", pixel.red, pixel.blue, pixel.green);
    }
    printf("\n");
  }
  free(pixels);
  free(reloaded);
  return 0;
}
