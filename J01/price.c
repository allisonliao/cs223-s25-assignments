/* Allison & Owen */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   srand(time(NULL));

   int price = rand() % 2001 + 3000;
   printf("Welcome to the Price is Right!\n");
   printf("Enter a guess to win a luxurious dishwasher: $");
   int arr[3];
   scanf("%d", &arr[0]);
   arr[1] = rand() % 2001 + 3000;
   arr[2] = rand() % 2001 + 3000;
   printf("AI contestant #1 guesses %d\n", arr[1]);
   printf("AI contestant #2 guesses %d\n", arr[2]);
   printf("The dishwasher cost %d\n", price);

   char output[128];
   strcpy(output, "Sorry. No one wins the dishwasher. I'm keeping it");
   
   if (arr[0] <= price) {
      strcpy(output, "Congratulations!! You win the dishwasher!");
   } else { arr[0] = 0;}
   if (arr[1] <= price && arr[1] > arr[0]) {
      strcpy(output, "AI contestant #1 wins the dishwasher!");
   } else { arr[1] = 0;}
   if (arr[2] <= price && arr[2] > arr[0]) {
      strcpy(output, "AI contestant #2 wins the dishwasher!");
   }
   
   printf("%s\n",output);
   
   return 0;
}

