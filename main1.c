#include "linked_list.h"
#include <stdio.h>

int list_print_nth(struct Node *head, unsigned index) {
  struct Node *node = list_node_at(head, index);
  if (!node)
    return 0;
  printf("%uth element of the list is %d\n", index, node->value);
  return 1;
}

int main() {
  struct Node *list = NULL;
  for (;;) {
    int value;
    if (scanf("%d", &value) == EOF)
      break;
    list_add_front(&list, value);
  }
  printf("The sum of the elements of the list is %d\n", list_sum(list));
  list_free(list);
  return 0;
}
