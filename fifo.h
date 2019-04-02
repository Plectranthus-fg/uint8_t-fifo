#include <stdint.h>
int fifo_in(uint8_t);
uint8_t fifo_out();
typedef struct node_st{
  uint8_t data;
  struct node_st *next, *prev;
} node_t;

typedef struct {
  node_t head,end;
  int size;
} llist_t;