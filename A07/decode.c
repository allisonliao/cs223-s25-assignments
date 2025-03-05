/*----------------------------------------------
 * Author: Allison Liao
 * Date: 03/06/25
 * Reads PPM file and outputs secret message.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w, h;
  unsigned int result = 0b0;
  
  // get pixels
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  char* res = malloc(w * h * 3);
  int c = 0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      c++;
      unsigned int mask = 0b1;
      unsigned int new = 0;

      new = (pixels[i  *h + j].red - '0' ) & mask;
      res[3 * (i * h + j)] = new + '0';
  
      new = (pixels[i * h + j].green - '0' ) & mask;
      res[3 *(i * h + j) + 1] = new + '0';
    
      new = (pixels[i * h + j].blue - '0' ) & mask;
      res[3 * (i * h + j) + 2] = new + '0';
    }
  }
  printf("Max number of characters in the image: %lu\n", strlen(res)/8);

  unsigned int var = 0;
  char* message = malloc(strlen(res) / 8);
  for (int i = 1; i <= strlen(res); i++) {
    var <<= 1;
    var |= (res[i-1] - '0');
    if (i % 8 == 0) {
      message[i/8 - 1] = var;
      var = 0;
    }
    
  }
  printf("%s", message);

  return 0;
}

