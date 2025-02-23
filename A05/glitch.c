/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Reads PPM file and writes 'glitched' version.
 ---------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"

void glitch(struct ppm_pixel *pixels, int w, int h) {
  srand(time(NULL));

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int idx = i * w + j;
      int shift = rand() % 3;
      pixels[idx].red = (pixels[idx].red << shift) & 255;
      pixels[idx].green = (pixels[idx].green << shift) & 255;
      pixels[idx].blue = (pixels[idx].blue << shift) & 255;
    }
  }
}

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  int w, h;

  struct ppm_pixel *pixels = read_ppm(filename, &w, &h);
  if (!pixels) {
    printf("Failed to read PPM. Exiting...");
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", filename, w, h);

  glitch(pixels, w, h);

  char output_name[64];
  snprintf(output_name, sizeof(output_name), "%.*s-glitch.ppm", (int) (strlen(filename)-4), filename);

  write_ppm(output_name, pixels, w, h);

  free(pixels);
  return 0;
}
