#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  char string[32];
  int ind = 2;
  while (argv[1][ind] != '\0') {
    string[ind - 2] = argv[1][ind];
    ind++;
  }
  string[ind - 2] = '\0';
  printf("string = %s\n", string);

  if (argv[1][1] == 'b') {
    int num = atoi(string);
    unsigned int mask = 0b1;
    int result = 0;

    for (int i = strlen(string) - 1; i >= 0; i--) {
      mask = 0b1 << i;
      if (mask & num)
        result = result * 2 + 1;
      else
        result = result * 2;
    }
    printf("result = %d\n", result);

  }

  else if (argv[1][1] == 'x') {
    // hex input
    int result = 0;

    for (int i = 0; string[i] != '\0'; i++) {
      int value = 0;
      char ch = string[i];
      if (ch >= '0' && ch <= '9') {
        value = ch - '0';
      } else if (ch >= 'A' && ch <= 'F') {
        value = ch - 'A' + 10;
      } else if (ch >= 'a' && ch <= 'f') {
        value = ch - 'a' + 10;
      } else printf("Error, incorrect he input.");
      
      result = (result << 4) | value;
    }

    printf("result = %d\n", result);
  }
  
  return 0;
}
