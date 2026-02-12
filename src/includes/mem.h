#ifndef MEM_H
#define MEM_H

struct mem_block {
  unsigned int size;
  unsigned int is_free;
  struct mem_block* next;
} __attribute__((packed));

void mem_setup();
void* malloc(unsigned int size);
void free(void *ptr);

#endif