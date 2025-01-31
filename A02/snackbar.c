/***************************************************
 * snackbar.c
 * Author: Allison Liao
 * Maintains a list of snacks for purchase.
 */
#include <stdio.h>
#include <string.h>

int main() {
  struct snack {
    double cost;
    char name[64];
    int quantity;
  };

  struct snack snack_array[3];

  struct snack cheerios = {.name = "Cheerios", .cost = 3.50, .quantity = 3};
  struct snack reeses = {.name = "Reese's Cups", .cost = 1.50, .quantity = 6};
  struct snack bananas = {.name = "Bananas", .cost = 0.50, .quantity = 0};

  snack_array[0] = cheerios;
  snack_array[1] = reeses;
  snack_array[2] = bananas;

  printf("Welcome to Steven Struct's Snack Bar.\n\n");
  printf("How much money do you have? ");
  double money;
  scanf("%lf", &money);

  printf("\n0) %s\t\tcost: $%.2lf\tquantity: %d\n", cheerios.name, cheerios.cost, cheerios.quantity);
  printf("1) %s\t\tcost: $%.2lf\tquantity: %d\n", reeses.name, reeses.cost, reeses.quantity);
  printf("2) %s\t\tcost: $%.2lf\tquantity: %d\n", bananas.name, bananas.cost, bananas.quantity);

  printf("\nWhat snack would you like to buy? [0,1,2] ");
  int choice;
  scanf("%d", &choice);

  if (choice >= sizeof(snack_array)/sizeof(snack_array[0]) || choice < 0) {
    printf("Invalid choice!\n");
  } else {
    int remaining = money - snack_array[choice].cost;
    if (remaining < 0) {
      printf("You can't afford it!\n");
    } else {
      if (snack_array[choice].quantity-1<0) {
        printf("Sorry, we are out of %s.\n", snack_array[choice].name);
      } else {
        printf("You bought %s.\n", snack_array[choice].name);
        printf("You have $%d left.\n", remaining);
      }
    }
  }

  return 0;
}
