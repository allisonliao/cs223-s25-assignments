#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  printf("Enter a string: ");
  char input[32];
  scanf("%s", input);

  int length = strlen(input);
  // allocate empty array
  char* array = malloc(sizeof(char) * length * length);
  memset(array, ' ', length * length);

  for (int i = 0; i < length; i++) {
    // first row
    array[i] = input[i];

    // last row
    array[(length - 1) * length + i] = input[i];

    // diagonal
    array[i * length + i] = input[i];
  }

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      //if (array[i*length + j] != NULL) {
        printf("%c ", array[i * length + j]);
      //} else {
      //  printf("  ");
      //}
    }
    printf("\n");
  }

  free(array);

  return 0;
}
