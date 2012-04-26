#ifndef BST_GENERATOR_H
#define BST_GENERATOR_H

/* since it's a binary search tree, make sure
 * MAX_NUM_NODES <= MAX_INT + 1.
 */
#define MAX_NUM_NODES 1000
#define MAX_INT 1000
#define NON_ELEMENT -1

struct node {
  int d;
  struct node* left;
  struct node* right;
};

void random_bst();
struct node* create_node_bst(int d);
int insert_bst(struct node** root, int d);
struct node* generate_bst(int num_nodes);
void destruct_bst(struct node* root);
int find_bst(struct node* root, int d);
void pre_order_bst(struct node* root);
void post_order_bst(struct node* root);
void in_order_bst(struct node* root);
void level_order_bst(struct node* root);
int _is_bst(struct node* root, int max, int min);
int is_bst(struct node* root);

#endif
