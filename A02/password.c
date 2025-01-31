/***************************************************
 * password.c
 * Author: 
 * Creates a bad password from input.
 */
#include <stdio.h>
#include <string.h>

int main() {
  printf("Enter a word: ");
  char input[100];
  scanf("%s", input);

  char curr;

  for (int i = 0; i < strlen(input); i++) {
    curr = input[i];
    if (curr == 97) {
      // character is 'a'
      input[i] = '@';
    } else if (curr == 101) {
      // character is 'e'
      input[i] = '3';
    } else if (curr == 108) {
      // character is 'l'
      input[i] = '1';
    }
  }

  printf("Your bad password is %s\n", input);

  return 0;
}
