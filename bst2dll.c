/*
 * This program transform a doubly-linked list(dll) to a
 * binary search tree(bst) in place.
 * In this program, left pointer is used to point to the previous node, and right
 * pointer is used to point to the next node in the dll.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bst_generator.h"

/* doubly-linked list. */
struct dll {
  struct node* head;
  struct node* tail;
};

void bst2dll(struct node* root, struct dll* list); 
/* @param head_tail stores either head or tail. */
void _bst2dll(struct node* root, struct node** head, struct node** tail);
void print_dll(struct dll list);
void destruct_dll(struct dll list);

int
main(int argc, char** argv) {
  random_bst();

  struct node* bst_root = generate_bst(20);
  printf("Pre-order\n");
  pre_order_bst(bst_root);
  printf("\n");
  printf("level-order\n");
  level_order_bst(bst_root);
  printf("\n");
  printf("Is a bst? %d\n", is_bst(bst_root));

  in_order_bst(bst_root);
  printf("\n");

  struct dll list;
  bst2dll(bst_root, &list);
  print_dll(list);
  destruct_dll(list);

  return 0;
}

void
bst2dll(struct node* root, struct dll* list) {
  if (root == NULL) {
    list->head = NULL;
    list->tail = NULL;
    return;
  }
  _bst2dll(root, &(list->head), &(list->tail));
}

void
_bst2dll(struct node* root, struct node** head, struct node** tail) {
  if (root == NULL) {
    *head = NULL;
    *tail = NULL;
    return;
  }
  struct node* lhead;
  struct node* ltail;
  _bst2dll(root->left, &lhead, &ltail);
  struct node* rhead;
  struct node* rtail;
  _bst2dll(root->right, &rhead, &rtail);

  root->left = ltail;
  if (ltail != NULL) {
    ltail->right = root;
  }
  root->right = rhead;
  if (rhead != NULL) {
    rhead->left = root;
  }
  if (lhead != NULL) {
    *head = lhead;
  } else {
    *head = root;
  }
  if (rtail != NULL) {
    *tail = rtail;
  } else {
    *tail = root;
  }
}

void
print_dll(struct dll list) {
  struct node* tmp = list.head;
  while (tmp != NULL) {
    printf("%d ", tmp->d);
    tmp = tmp->right;
  }
  printf("\n");
}

void
destruct_dll(struct dll list) {
  struct node* tmp = list.head;
  while (list.head != NULL) {
    tmp = list.head;
    list.head = list.head->right;
    free(tmp);
  }
}
