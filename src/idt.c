#include "includes/idt.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  always0;
    uint8_t  flags;       // Attributes (P, DPL, Type)
    uint16_t base_high;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t limit;       // Total size - 1
    uint32_t base;        // Base address
} __attribute__((packed));

void idt_set_gate(uint8_t index, uint32_t func_addr, uint16_t selector, uint8_t flags);
void pic_remap();
extern void irq_handle_keyboard(void);
extern void irq_dummy(void);

struct idt_entry idt_entries[IDT_MAX_SIZE];
struct idt_descriptor idt_table;

void idt_setup() {
  // We need to "reset" each gate
  for(int i = 0; i < IDT_MAX_SIZE; i++) {
    idt_set_gate(i, (uint32_t)irq_dummy, 0x08, 0x8E);
  }

  idt_table.limit = (sizeof(struct idt_entry) * IDT_MAX_SIZE) - 1;
  idt_table.base = (uint32_t) &idt_entries;

  // lidt => Load Interrupt Descriptor Table
  asm volatile ("lidt %0" :: "m"(idt_table));

  // Configuring ports
  idt_set_gate(33, (uint32_t) irq_handle_keyboard, 0x08, 0x8E);

  pic_remap(); 
  asm volatile ("sti"); // TODO: O que é isso aqui? A IA pediu para implementar isso aqui
}

// TOD: O que é isso? A IA pediu para implementar isso aqui
void pic_remap() {
  // Inicialização básica
  outb(0x20, 0x11); outb(0xA0, 0x11);
  // Offset: Master=32 (0x20), Slave=40 (0x28)
  outb(0x21, 0x20); outb(0xA1, 0x28);
  // Cascata
  outb(0x21, 0x04); outb(0xA1, 0x02);
  // Modo 8086
  outb(0x21, 0x01); outb(0xA1, 0x01);
  // Habilita tudo (máscara zero)
  outb(0x21, 0x00); outb(0xA1, 0x00);
}

void idt_set_gate(uint8_t index, uint32_t func_addr, uint16_t selector, uint8_t flags) {
  idt_entries[index].base_low = func_addr & 0xFFFF;
  idt_entries[index].base_high = (func_addr >> 16) & 0xFFFF;

  idt_entries[index].selector = selector;
  idt_entries[index].always0 = 0;
  idt_entries[index].flags = flags;
}