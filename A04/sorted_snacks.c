/*----------------------------------------------
 * Author:
 * Date:
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[64];
  double cost;
  int quantity;
};

struct node {
  struct snack val;
  struct node *next;
};

struct node *insert_first(struct node *head, struct snack data) {
  struct node *new = malloc(sizeof(struct node));
  new->val = data;
  new->next = head;
  return new;
};

int clear(struct node *head) {
  struct node *temp = head;
  while (temp->next != NULL) {
    head = temp->next;
    free(temp);
    temp = head;
  }
  free(temp);
  return 0;
};

void printList(struct node *head) {
  int index = 0;
  while (head != NULL) {
    struct snack curr = head->val;
    printf("%d) %s\t\t\tcost: $%.2lf\tquantity: %d\n", index, curr.name,
           curr.cost, curr.quantity);
    head = head->next;
    index++;
  }
};

struct node* sortCost(struct node *head) {
  struct node* p = head;
  int swap = 1;
  while (swap) {
    swap = 0;
    struct node* prev = NULL;
    for (struct node* p = head; p != NULL && p->next != NULL; prev = p, p = p->next) {
      //struct node* next = head->next;
      struct node* temp = p->next;
      if (temp->val.cost < p->val.cost) {
        swap++;
        if (prev == NULL) {
          p->next = temp->next;
          temp->next = p;
          head = temp;
        } else {
          p->next = temp->next;
          temp->next = p;
          prev->next = temp;
        }
      }
    }
  }
  return head;
}

int sortName(struct node *head) { return 0; }

int sortQuantity(struct node *head) { return 0; }

int main() {
  int num;
  printf("Enter a number of snacks: ");
  scanf("%d", &num);

  struct node *head = NULL;

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

    // create snack from input
    struct snack curr = {.cost = cost, .quantity = quantity};
    strcpy(curr.name, name);

    head = insert_first(head, curr);
  }

  printList(head);

  head = sortCost(head);

  printList(head);

  return 0;
}