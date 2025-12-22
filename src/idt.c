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
void idt_pic_remap();
extern void irq_handle_keyboard(void);
extern void irq_dummy(void);

struct idt_entry idt_entries[IDT_MAX_SIZE];
struct idt_descriptor idt_table;

void idt_setup() {
  // We need to "reset" each gate
  for(int i = 0; i < IDT_MAX_SIZE; i++) {
    idt_set_gate(i, (uint32_t)irq_dummy, 0x08, 0x8E);
  }

  // Configuring ports

  // Configuring the keyboard
  //
  // Index               => 34th => 33 in memory
  // irq_handle_keyboard => Assembly code that access at PIC 0x60
  // selector            => GDT index, which is the 1st segment => 0000 1000b
  // flags               => 0x80 + 0x0E => 0x80 equals to 1000 1110b (present, kernel access and 32 bits)
  idt_set_gate(33, (uint32_t) irq_handle_keyboard, 0x08, 0x8E);

  // Finishing setting up the descriptor
  idt_table.limit = (sizeof(struct idt_entry) * IDT_MAX_SIZE) - 1;
  idt_table.base = (uint32_t) &idt_entries;

  // Now, we need to remap the PICs (Master and Slave) to work with 32 bits
  idt_pic_remap(); 

  // lidt => Load Interrupt Descriptor Table
  asm volatile ("lidt %0" : : "m"(idt_table));
  asm volatile ("sti"); // Sets the interrupt flag (IF) as TRUE
}

void idt_set_gate(uint8_t index, uint32_t func_addr, uint16_t selector, uint8_t flags) {
  idt_entries[index].base_low = func_addr & 0xFFFF;
  idt_entries[index].base_high = (func_addr >> 16) & 0xFFFF;

  idt_entries[index].selector = selector;
  idt_entries[index].always0 = 0;
  idt_entries[index].flags = flags;
}

void idt_pic_remap() {
  // Sends to PIC Master and Slave we will send 3 commands
  outb(0x20, 0x11); outb(0xA0, 0x11);
  // Offset: Master=32 (0x20), Slave=40 (0x28)
  outb(0x21, 0x20); outb(0xA1, 0x28);
  // When Slaves sends signal to a Master's pin... It needs to send to CPU
  outb(0x21, 0x04); outb(0xA1, 0x02);
  // Sets chips to work with 32 bits architecture
  outb(0x21, 0x01); outb(0xA1, 0x01);

  // To finish the configuration...
  // We need to allow each PIC receive data from external hardware
  // to send to the CPU.
  outb(0x21, 0x00); outb(0xA1, 0x00);
}