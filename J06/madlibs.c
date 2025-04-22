#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 32

int main() {
  int num;
  int b;
  printf("Boolean:");
  scanf(" %d", &b);
  printf("Number:");
  scanf(" %d", &num);
  char** adjectives = malloc(num * sizeof(char*));
  for (int i = 0; i < num; i++) {
    adjectives[i] = malloc(MAXSIZE);
    printf("Adjective:");
    scanf(" %s", adjectives[i]);
  }
  printf("You are the most ");
  for (int i = 0; i < num - 1; i++) {
    printf("%s, ", adjectives[num - 1 - i]);
  }
  printf("and %s person that I know and you know its ", adjectives[0]);
  if (b) {
    printf("true!\n");
  } else {
    printf("false!\n");
  }

  for (int i = 0; i < num; i++) {
    free(adjectives[i]);
  }
  free(adjectives);
  return 0;
}
