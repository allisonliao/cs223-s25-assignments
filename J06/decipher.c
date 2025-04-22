#include <stdio.h>
#include <limits.h>

int main(int argc, char** argv) {
  FILE* fp = fopen(argv[1], "r");
  char c = fgetc(fp);
  while (c != EOF) {
    c = c >> 1;
    c = c & ~(1 << (CHAR_BIT - 1));
    printf("%c", c);
    c = fgetc(fp);
  }
  return 0;
}
