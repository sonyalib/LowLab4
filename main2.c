#include "higher_order.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

static FILE *io_file;
static void _print_space(int x) { fprintf(io_file, "%d ", x); }
static void _print_newline(int x) { fprintf(io_file, "%d\n", x); }
static int _square(int x) { return x * x; }
static int _cube(int x) { return x * x * x; }
static int _mul2(int x) { return 2 * x; }
static int _min(int x, int y) { return x < y ? x : y; }
static int _max(int x, int y) { return x > y ? x : y; }
static int _abs(int x) { return x < 0 ? -x : x; }
static int _add1(int x) { return x + 1; }

static int save(struct Node *head, char const *filename) {
  io_file = fopen(filename, "w");
  if (!io_file) return 0;
  foreach(_print_space, head);
  return !fclose(io_file);
}

static int load(struct Node **head, char const *filename) {
  int input;
  FILE *f = fopen(filename, "r");
  if (!f) return 0;
  for (; fscanf(f, "%d", &input) != EOF; head = &(*head)->next) {
    if (!list_add_front(head, input)) {
      printf("%d\n", input);
      fclose(f);
      return 0;
    }
  }
  return 1;
}

static int *buffer_pos;
static void append_to_buffer(int x) { *buffer_pos++ = x; }
static int read_from_buffer(int pos) { return buffer_pos[pos]; }

int serialize(struct Node *head, char const *filename) {
  FILE *f;
  unsigned len = list_length(head);
  int *buffer = malloc(sizeof(int) * len);
  if (!buffer) return 0;

  f = fopen(filename, "wb");
  if (!f) {
    free(buffer);
    return 0;
  }
  buffer_pos = buffer;
  foreach(append_to_buffer, head);
  if (fwrite(buffer, sizeof(int), len, f) != len) {
    free(buffer);
    fclose(f);
    return 0;
  }

  free(buffer);
  return !fclose(f);
}

static int deserialize(struct Node **head, char const *filename) {
  long pos;
  FILE *f = fopen(filename, "rb");
  if (!f) return 0;
  if (fseek(f, 0, SEEK_END) == -1) {
    fclose(f);
    return 0;
  }
  pos = ftell(f);
  if (pos == -1) {
    fclose(f);
    return 0;
  }
  printf("pos = %ld\n", pos);
  buffer_pos = malloc(pos);
  if (!buffer_pos) {
    fclose(f);
    return 0;
  }
  fseek(f, 0, SEEK_SET);
  if (fread(buffer_pos, sizeof(int), pos / sizeof(int), f) != pos / sizeof(int)) {
    free(buffer_pos);
    fclose(f);
    return 0;
  }

  *head = iterate(0, _add1, pos / sizeof(int));
  map_mut(read_from_buffer, *head);

  free(buffer_pos);
  fclose(f);
  return 1;
}

int main() {
  struct Node dummy = {NULL, 0};
  struct Node *list = &dummy;
  struct Node *tmp, *tmp2;

  for (;;) {
    int value;
    if (scanf("%d", &value) == EOF)
      break;
    list_add_front(&list->next, value);
    list = list->next;
  }
  list = dummy.next;

  io_file = stdout;

  puts("Whitespace separated");
  foreach(_print_space, list);

  puts("\nNewline separated");
  foreach(_print_newline, list);

  puts("Squares");
  tmp = map(_square, list);
  foreach(_print_space, tmp);
  list_free(tmp);
  puts("\n");

  puts("Cubes");
  tmp = map(_cube, list);
  foreach(_print_space, tmp);
  list_free(tmp);
  puts("\n");

  printf("Min is %d\n", foldl(list->value, _min, list));
  printf("Max is %d\n", foldl(list->value, _max, list));

  puts("Absolute values");
  map_mut(_abs, list);
  foreach(_print_space, list);
  puts("\n");

  puts("Iteration");
  tmp = iterate(1, _mul2, 10);
  foreach(_print_space, tmp);
  list_free(tmp);
  puts("\n");

  puts("Testing save/load");
  save(list, "file.txt");
  tmp = NULL;
  load(&tmp, "file.txt");

  io_file = stdout;
  foreach(_print_space, list);
  puts("");
  foreach(_print_space, tmp);
  puts("");

  tmp2 = list;
  while (tmp && tmp2) {
    if (tmp->value != tmp2->value) {
      printf("%d != %d!\n", tmp->value, tmp2->value);
      return 1;
    }
    tmp = tmp->next;
    tmp2 = tmp2->next;
  }
  if (tmp || tmp2) {
    puts("Lists have unequal length!");
    return 1;
  }
  puts("Lists for save/load are equal");
  list_free(tmp);

  puts("Testing serialize/deserialize");
  serialize(list, "file.dat");
  tmp = NULL;
  deserialize(&tmp, "file.dat");

  foreach(_print_space, list);
  puts("");
  foreach(_print_space, tmp);
  puts("");

  tmp2 = list;
  while (tmp && tmp2) {
    if (tmp->value != tmp2->value) {
      printf("%d != %d!\n", tmp->value, tmp2->value);
      return 1;
    }
    tmp = tmp->next;
    tmp2 = tmp2->next;
  }
  if (tmp || tmp2) {
    puts("Lists have unequal length!");
    return 1;
  }
  puts("Lists for serialize/deserialize are equal");
  list_free(tmp);

  list_free(list);
  return 0;
}
