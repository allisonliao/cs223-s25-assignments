#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "read_ppm.h"
#include "write_ppm.h"

#define THRESHOLD 200
#define BOX_SIZE 25
#define RADIUS (BOX_SIZE / 2)

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
unsigned char clamp_color(int val) {
  if (val < 0) return 0;
  if (val > 255) return 255;
  return (unsigned char)val;
}

int main(int argc, char* argv[]) {
  int width, height;
  struct ppm_pixel* original = read_ppm("earth-small.ppm", &width, &height);
  if (!original) {
    return 1;
  }

  int size = width * height;

  struct ppm_pixel* bright = malloc(sizeof(struct ppm_pixel) * size);
  struct ppm_pixel* blurred = malloc(sizeof(struct ppm_pixel) * size);
  struct ppm_pixel* result = malloc(sizeof(struct ppm_pixel) * size);

  if (!bright || !blurred || !result) {
    printf("Failed to allocate memory.\n");
    return 1;
  }

  // extract bright areas
  for (int i = 0; i < size; i++) {
    int brightness =
        (original[i].red + original[i].green + original[i].blue) / 3;
    if (brightness > THRESHOLD) {
      bright[i] = original[i];
    } else {
      bright[i].red = bright[i].green = bright[i].blue = 0;
    }
  }

  // box blur
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int r_sum = 0, g_sum = 0, b_sum = 0;
      int count = 0;

      for (int dy = -RADIUS; dy <= RADIUS; dy++) {
        for (int dx = -RADIUS; dx <= RADIUS; dx++) {
          int ny = row + dy;
          int nx = col + dx;

          if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
            int idx = ny * width + nx;
            r_sum += bright[idx].red;
            g_sum += bright[idx].green;
            b_sum += bright[idx].blue;
            count++;
          }
        }
      }

      int idx = row * width + col;
      blurred[idx].red = r_sum / count;
      blurred[idx].green = g_sum / count;
      blurred[idx].blue = b_sum / count;
    }
  }

  // ad blurred to original (clamped)
  for (int i = 0; i < size; i++) {
    result[i].red = clamp_color(original[i].red + blurred[i].red);
    result[i].green = clamp_color(original[i].green + blurred[i].green);
    result[i].blue = clamp_color(original[i].blue + blurred[i].blue);
  }

  // save result
  write_ppm("glow.ppm", result, width, height);

  // free
  free(original);
  free(bright);
  free(blurred);
  free(result);

  return 0;
}
