#include "includes/mem.h"

extern unsigned int heap_start;

void mem_setup() {
  struct mem_block* head = (struct mem_block*)&heap_start;
  head->is_free = 1;
  head->size = (1024 * 1024) - sizeof(struct mem_block); // Hardcoded 1MB size just for 1st block.
  head->next = 0;
}

void* malloc(unsigned int size) {
  struct mem_block* head = (struct mem_block*) heap_start;

  while (head) {
    // TODO: We must identify when we are out of memory

    if (head->is_free && head->size >= size) {
      head->is_free = 0;
      return (void *)(head + 1);
    }

    if (!head->next)
      break;
    
    head = head->next;
  }

  struct mem_block* new_block = (struct mem_block*)((char*) head + sizeof(struct mem_block) + head->size);
  new_block->size = size;
  new_block->is_free = 0;
  new_block->next = 0;
  head->next = new_block;

  return (void *)(new_block + 1);
}

void free(void *ptr) {
  struct mem_block* head = (struct mem_block*)ptr;
  head->is_free = 1;
}