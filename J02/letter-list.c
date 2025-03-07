#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node {
  char val;
  struct node *next;
};

struct node *insert_first(struct node *head, char data) {
  struct node *new = malloc(sizeof(struct node));
  new->val = data;
  new->next = head;
  return new;
};

void printList(struct node *head, char c) {
  while (head != NULL) {
    char curr = head->val;
    if (curr != c) {
      printf("%c",head->val);
    }
    head = head->next;
  }
  printf("\n");
}

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

int main()
{
  printf("Enter a word: ");
  char input[32];
  scanf(" %s", input);

  printf("Enter a character to remove: ");
  char c;
  scanf(" %c", &c);

  struct node *head = NULL;

  for (int i = strlen(input)-1; i >= 0; i--) {
    char x = input[i];
    head = insert_first(head, x);
  }

  printList(head, c);
  
  clear(head);
  return 0;
}
