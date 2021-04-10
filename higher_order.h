#ifndef _HIGHER_ORDER_H_
#define _HIGHER_ORDER_H_

struct Node;

void foreach(void (*func)(int), struct Node *head);
struct Node *map(int (*func)(int), struct Node *head);
void map_mut(int (*func)(int), struct Node *head);
int foldl(int acc, int (*func)(int, int), struct Node *head);
struct Node *iterate(int acc, int (*func)(int), unsigned repeats);

#endif
