/***************************************************
 * cypher.c
 * Author: 
 * Implements a shift cypher, given a shift.
 */
#include <stdio.h>
#include <string.h>

int main() {

  printf("Enter a word: ");
  char buffer[64];
  char word[100];
  scanf("%s", word);
  strcpy(buffer, word);
  
  printf("Enter a shift: ");
  int shift;
  scanf("%d", &shift);

  char curr;

  for (int i = 0; i < strlen(buffer); i++) {
    curr = buffer[i];
    if (curr > 122 -shift) {
      buffer[i] = curr - 26 + shift;
    } else {
      buffer[i] = curr + shift;
    }
  }

  printf("Your cypher is: %s\n", buffer);

  return 0;
}
