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
  scanf("%s", input);

  printf("Enter a character to remove: ");
  char c;
  scanf("%c", &c);

  struct node *head = NULL;

  for (int i = strlen(input)-1; i >= 0; i++) {
    insert_first(head, input[i]);
  }

  while (head != NULL) {
    char curr = head->val;
    // remove char
    // if (curr == c) {
    //   struct node *temp = head->next;
    //   head->next = temp->next;
      
    // }

    // print
    if (curr != c) {
      printf("%c",head->val);
    }
    head = head->next;
  }
  return 0;
}
