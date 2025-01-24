/***************************************************
 * mathgame.c
 * Author: Allison Liao
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Welcome to Math Game!\n");
  printf("How many rounds do you want to play? ");
  int rounds;
  scanf("%d", &rounds);

  int corrAnswers = 0;

  int val1, val2;
  int ans;

  for(int i = rounds; i > 0; i--) {
    val1 = rand() % 9;
    val2 = rand() % 9;

    printf("\n%d + %d = ? ", val1, val2);
    scanf("%d", &ans);

    if(val1 + val2 == ans) {
      corrAnswers++;
      printf("Correct!\n"); 
    }
    else{
      printf("Incorrect :(\n");
    }
  }
  
  printf("You answered %d/%d correctly.\n", corrAnswers, rounds);
  
  return 0;
}
