/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/07/25
 * Repeats given string given amount of times
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char word[32];
  int count;
  printf("Enter a word: ");
  scanf("%s", word);
  printf("Enter a count: ");
  scanf("%d", &count);

  char* output = malloc(sizeof(word) * count);
  memset(output, 0, sizeof(word) * count);
  if (output == NULL) {
    printf("Cannot allocate new string. Exiting...\n");
    return 1;
  }

  for (int i = 0; i < count; i++) {
    strcat(output, word);
  }

  printf("Your word is: %s\n", output);

  free(output);
  return 0;
}
