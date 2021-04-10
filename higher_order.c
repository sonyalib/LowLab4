#include "higher_order.h"
#include "linked_list.h"

void foreach(void (*func)(int), struct Node *head) {
  for (; head; head = head->next)
    func(head->value);
}

struct Node *map(int (*func)(int), struct Node *head) {
  struct Node dummy = {0, 0};
  struct Node *new_tail = &dummy;
  for (; head; head = head->next, new_tail = new_tail->next)
    list_add_front(&new_tail->next, func(head->value));
  return dummy.next;
}

void map_mut(int (*func)(int), struct Node *head) {
  for (; head; head = head->next)
    head->value = func(head->value);
}

int foldl(int acc, int (*func)(int, int), struct Node *head) {
  for (; head; head = head->next)
    acc = func(acc, head->value);
  return acc;
}

struct Node *iterate(int acc, int (*func)(int), unsigned repeats) {
  struct Node dummy = {0, 0};
  struct Node *new_tail = &dummy;
  unsigned i;
  for (i = 0; i < repeats; ++i) {
    list_add_front(&new_tail->next, acc);
    new_tail = new_tail->next;
    acc = func(acc);
  }
  return dummy.next;
}
