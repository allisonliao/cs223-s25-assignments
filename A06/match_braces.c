/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/28/25
 * Uses a stack to identify matching brackets.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  struct brace *val;
  struct node *next;
};

struct brace {
  char type;
  int line;
  int col;
};

struct node *insert_first(struct node *head, struct brace* data) {
  struct node *new = malloc(sizeof(struct node));
  new->val = data;
  new->next = head;
  return new;
};

void printList(struct node *head, struct brace* c) {
  while (head != NULL) {
    struct brace* curr = head->val;
    if (curr != c) {
      printf("%c, (%d, %d)",head->val->type, head->val->col, head->val->line);
    }
    head = head->next;
  }
  printf("\n");
}

int clearStack(struct node *head) {
  struct node *temp = head;
  while (temp->next != NULL) {
    head = temp->next;
    free(temp);
    temp = head;
  }
  free(temp);
  return 0;
};

struct node *pop(struct node *head) {
  if (head == NULL) {
    printf("Stack underflow error. Exiting...");
    exit(1);
  }
  struct node *temp = head;
  head = head->next;
  return temp;
};

struct node *push(struct node *head, struct brace* data) {
  return insert_first(head, data);
};

int main(int argc, char** argv)
{
  FILE* file;
  file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("Cannot open file: %s. Exiting...", argv[1]);
    return 1;
  }

  // go through input, pushing when '{' is found, popping when '}' found
  struct node *head = NULL;
  int curr = fgetc(file);

  int line = 0;
  int col = 1;

  while(curr != -1) {
    if (curr == '\n') {
      line++;
      col = 0;
    }
    col++;
    if (curr == '{') {
      struct brace *brace = malloc(sizeof(struct brace));
      brace->type = curr;
      brace->col = col;
      brace->line = line;
      head = push(head, brace);
    }
    else if (curr == '}') {
      struct node *popped = pop(head);
      struct brace *popped_val = popped->val;
      int l = popped_val->line;
      int c = popped_val->col;
      if (popped_val->type != '{') {
        printf("Unmatched brace found on Line %d and Column %d", line, col);
      } else {
        printf("Found matching braces: (%d, %d) -> (%d, %d)", l, c, line, col);
      }
      free(popped);
    }
    curr = fgetc(file);
  }

  clearStack(head);
  return 0;
}

