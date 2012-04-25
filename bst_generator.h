#ifndef BST_GENERATOR_H
#define BST_GENERATOR_H

/* since it's a binary search tree, make sure NUM_NODES <= MAX_INT + 1. */
/* TODO: should let users pass NUM_NODES to generate_bst(). */
#define NUM_NODES 10
#define MAX_INT 1000
#define NON_ELEMENT -1

struct node {
  int d;
  struct node* left;
  struct node* right;
};

struct node* create_node_bst(int d);
int insert_bst(struct node** root, int d);
struct node* generate_bst();
void destruct_bst(struct node* root);
int find_bst(struct node* root, int d);
void pre_order_bst(struct node* root);
void post_order_bst(struct node* root);
void in_order_bst(struct node* root);
void level_order_bst(struct node* root);
int _is_bst(struct node* root, int max, int min);
int is_bst(struct node* root);

#endif
