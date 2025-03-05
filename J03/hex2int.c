#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  char string[32];
  int ind = 2;
  while (argv[1][ind] != '\0') {
    string[ind-2] = argv[1][ind];
    ind++;
  }
  string[ind-2] = '\0'; 
  printf("string = %s\n", string);


  if (argv[1][1] == 'b') {
    int num = atoi(string);
    unsigned int mask = 0b1;
    int result = 0;

    for (int i = strlen(string)-1; i >= 0; i--) {
      mask = 0b1 << i;
      if (mask & num) result = result * 2 + 1;
      else result = result * 2;
    }
    printf("result = %d\n", result);

  }

  else if (argv[1][1] == 'x') {
    // hex input

    int num = atoi(string);
    unsigned int mask = 0xF;
    int result = 0;

    for (int i = strlen(string)-1; i >= 0; i--) {
      mask = 0xF << i * 4;
      unsigned int curr = mask & num;
      curr = curr >> i*4;
      printf("curr = %d", curr);
      result = result *16 + curr;
    }
    printf("result = %d\n", result);


  }
  return 0;
}
