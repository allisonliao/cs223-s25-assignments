/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/28/25
 * Implements a binary search tree.
 ---------------------------------------------*/

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_node* find(const char* name, struct tree_node* root) {
  struct tree_node* curr = root;
  while (curr) {
    int cmp = strcmp(name, curr->data.name);
    if (cmp == 0) {
      return curr;
    }
    curr = (cmp < 0) ? curr->left : curr->right;
  }
  return NULL;
}

struct tree_node* insert(const char* name, struct tree_node* root) {
  // create new node
  struct tree_node* new = malloc(sizeof(struct tree_node));
  strcpy(new->data.name, name);

  struct tree_node* curr = root;
  while (curr) {
    if (strcmp(new->data.name, curr->data.name) < 0) {
      if (curr->left == NULL) {
        curr->left = new;
        return root;
      }
      curr = curr->left;
    } else {
      if (curr->right == NULL) {
        curr->right = new;
        return root;
      }
      curr = curr->right;
    }
  }

  // empty tree case
  return new;
}

void clear(struct tree_node* root) {
  if (root) {
    clear(root->left);
    clear(root->right);
    free(root);
  }
}

void printIndentation(int n) {
  for (int i = 0; i < n; i++) {
    printf(" ");
  }
}

void indentPrint(struct tree_node* root, int n, char* prefix) {
  if (root) {
    printIndentation(n);
    printf("%s%s\n", prefix, root->data.name);
    indentPrint(root->left, n + 1, "l:");
    indentPrint(root->right, n + 1, "r:");
  }
}

void print(struct tree_node* root) { indentPrint(root, 0, ""); }

void printSorted(struct tree_node* root) {
  if (root) {
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
  }
}
