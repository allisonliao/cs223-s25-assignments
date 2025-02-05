/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/07/25
 * Maintains a snackbar that users may edit
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  double cost;
  char name[64];
  int quantity;
};

void print_snack(void *obj, int num) {
  struct snack *array = obj;
  for (int i = 0; i < num; i++) {
    struct snack curr = array[i];
    printf("%d) %s\t\t\tcost: $%.2lf\tquantity: %d\n",i,curr.name,curr.cost, curr.quantity);
  }
};

int main() {

  int num;
  printf("Enter a number of snacks: ");
  scanf("%d", &num);

  struct snack* arr = malloc(sizeof(struct snack) * (num));
  if (arr == NULL) {
    printf("Cannot allocate struct array. Exiting...\n");
    return 1;
  }

  for (int i = 0; i < num; i++) {
    // initialize snack variables
    char name[32];
    double cost;
    int quantity;

    // fill variables from input
    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a cost: ");
    scanf("%lf", &cost);
    printf("Enter a quantity: ");
    scanf("%d", &quantity);

    // store snack in array
    arr[i].cost = cost;
    arr[i].quantity = quantity;
    strcpy(arr[i].name, name);
  }

  printf("Welcome to Dynamic Donna's Snack Bar.\n");

  print_snack(arr, num);
  
  free(arr);
  return 0;
}
