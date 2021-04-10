#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

struct Node {
  struct Node *next;
  int value;
};

struct Node *list_create(int value);
int list_add_front(struct Node **head, int value);
int list_add_back(struct Node **head, int value);
int list_get(struct Node *head, unsigned index);
void list_free(struct Node *head);
unsigned list_length(struct Node *head);
struct Node *list_node_at(struct Node *head, unsigned index);
int list_sum(struct Node *head);

#endif
