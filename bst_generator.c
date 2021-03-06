/* currently assuming all elements are non-negative integers */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bst_generator.h"

void
random_bst() {
  srand(time(NULL));
}

struct node*
create_node_bst(int d) {
  struct node* n = (struct node*)malloc(sizeof(struct node));
  assert(n != NULL);
  n->d = d;
  n->left = NULL;
  n->right = NULL;
  return n;
}

/*
 * returns 1 on success, 0 on failure.
 */
int
insert_bst(struct node** root, int d) {
  if (*root == NULL) {
    *root = create_node_bst(d);
    return 1;
  }
  struct node* n = *root;
  while (1) {
    if (n->d == d) {
      return 0;
    }
    if (n->d > d) {
      if (n->left == NULL) {
        n->left = create_node_bst(d);
        break;
      }
      n = n->left;
    } else {
      if (n->right == NULL) {
        n->right = create_node_bst(d);
        break;
      }
      n = n->right;
    }
  }
  return 1;
}

struct node*
generate_bst(int num_nodes) {
  assert(MAX_NUM_NODES <= MAX_INT);
  assert(num_nodes <= MAX_NUM_NODES);

  struct node* root = NULL;
  int d;
  int i = 0;
  while (i < num_nodes) {
    d = rand() % (MAX_INT + 1);
    if (insert_bst(&root, d)) {
      i++;
    }
  }
  return root;
}

void
destruct_bst(struct node* root) {
  if (root == NULL) {
    return;
  }
  destruct_bst(root->left);
  destruct_bst(root->right);
  free(root);
}

/*
 * returns 1 if d is in the bst rooted at root, 0 if not.
 */
int
find_bst(struct node* root, int d) {
  while (root != NULL) {
    if (root->d == d) {
      return 1;
    }
    if (root->d < d) {
      root = root->right;
    } else {
      root = root->left;
    }
  }
  return 0;
}

void
pre_order_bst(struct node* root) {
  if (root == NULL) {
    return;
  }
  printf("%d ", root->d);
  pre_order_bst(root->left);
  pre_order_bst(root->right);
}

void
post_order_bst(struct node* root) {
  if (root == NULL) {
    return;
  }
  post_order_bst(root->left);
  post_order_bst(root->right);
  printf("%d ", root->d);
}

void
in_order_bst(struct node* root) {
  if (root == NULL) {
    return;
  }
  in_order_bst(root->left);
  printf("%d ", root->d);
  in_order_bst(root->right);
}

void
level_order_bst(struct node* root) {
  struct node* queue[MAX_NUM_NODES];
  int levels[MAX_NUM_NODES];
  int level = 0;
  int front = 0;
  int rear = 0;
  levels[rear] = level;
  queue[rear++] = root;
  while (front < rear) {
    level = levels[front];
    root = queue[front++];
    printf("(%d, %d) ", level, root->d);
    if (root->left != NULL) {
      levels[rear] = level + 1;
      queue[rear++] = root->left;
    }
    if (root->right != NULL) {
      levels[rear] = level + 1;
      queue[rear++] = root->right;
    }
  }
}

/*
 * max and min should initially be NON_ELEMENT
 */
int
_is_bst(struct node* root, int max, int min) {
  if (root == NULL) {
    return 1;
  }
  if (max != NON_ELEMENT && root->d > max) {
    return 0;
  }
  if (min != NON_ELEMENT && root->d < min) {
    return 0;
  }
  return (
    _is_bst(root->left, root->d, min) &&
    _is_bst(root->right, max, root->d)
  );
}

int
is_bst(struct node* root) {
  return _is_bst(root, NON_ELEMENT, NON_ELEMENT);
}

/*
int
main(int argc, char** argv) {
  random_bst();
  struct node* root = generate_bst(10);
  printf("Pre-order: ");
  pre_order_bst(root);
  printf("\n");
  printf("In-order: ");
  in_order_bst(root);
  printf("\n");
  printf("Post-order: ");
  post_order_bst(root);
  printf("\n");
  printf("Level-order: ");
  level_order_bst(root);
  printf("\n");
  printf(
    "Is a binary search tree? %d\n", is_bst(root)
  );
  destruct_bst(root);
  return 0;
}
*/
