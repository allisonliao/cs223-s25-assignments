/* Allison & Owen */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   printf("Enter digits: ");
   char input[31];
   scanf("%s", input);
   int digits[10] = {0};

   for (int i = 0; i < strlen(input); i++) {
      digits[input[i] - '0']++;
   }

   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < digits[i]; j++) {
         printf("%d ", i);
      }
   }
  
   return 0;
}
