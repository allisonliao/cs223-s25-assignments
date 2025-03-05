/*----------------------------------------------
 * Author: Allison Liao
 * Date: 03/06/25
 * Takes input 64 bit unsigned long, outputs bpp.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  char output[64];
  memset(output, ' ', 64);

  for (int i = 0; i < 64; i++) {
    unsigned long mask = 0x1UL << i;
    if (mask & img) {
      output[63-i] = '@';
    }
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%c", output[i * 8 + j]);
    }
    printf("\n");
  }
  return 0;
}
