#include "fifo.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

llist_t llist;

void node_add_next(node_t *node) {}

void llist_init() { llist.size = 0; }

int fifo_in(uint8_t data) {
  node_t *nodeptr;
  nodeptr = malloc(sizeof(node_t));
  nodeptr->data = data;
  if (llist.size > 0 && llist.size <63) {
    nodeptr->next = &llist.end;
    nodeptr->prev = llist.end.prev;
    llist.end.prev->next = nodeptr;
    llist.end.prev = nodeptr;
    llist.size += 1;
  } else if (llist.size == 0) {
    nodeptr->prev = &llist.head;
    nodeptr->next = &llist.end;
    llist.head.next = nodeptr;
    llist.end.prev = nodeptr;
    llist.size += 1;
  }else if(llist.size > 62){
    fifo_out();
    nodeptr->next = &llist.end;
    nodeptr->prev = llist.end.prev;
    llist.end.prev->next = nodeptr;
    llist.end.prev = nodeptr;
    llist.size += 1;
  }
  return 0;
}

uint8_t fifo_out() {
  uint8_t data;
  if (llist.size != 1) {
    data = llist.head.next->data;
    llist.head.next = llist.head.next->next;
    llist.head.next->prev = &llist.head;
    llist.size -= 1;
  } else if (llist.size == 0) {
    return 0;
  }else if(llist.size == 1){
    return 255;
  }
  return data;
}

int main() {
  for (uint8_t i = 0; i < 200; i++) {
    fifo_in(i);
  }
  for (uint8_t i = 0; i < 100; i++) {
    printf("%d\n", fifo_out());
  }
  return 0;
}