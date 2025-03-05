#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  //printf("%s\n", argv[1]);
  int input = atoi(argv[1]);
  //printf("%d\n", input);

  printf("0x ");
  unsigned int mask = 0xF;
  for (int i = 7; i >= 0; i--) {
    mask = 0xF << i*4;
    unsigned int curr = mask & input;
    curr = curr >> i*4;
    printf("%X", curr);
    if ((i) % 2 == 0) {
      printf(" ");
    }
  }

  printf("\n");
  printf("0b ");
  int bmask = 0b1;
  for (int i = 31; i >= 0; i--) {
    bmask = 0b1 << i;
    int curr = 0;
    if (bmask & input) curr = 1;
    printf("%d", curr);
    if ((i) % 4 == 0) {
      printf(" ");
    }
  }

  printf("\n");
  
  return 0;
}
