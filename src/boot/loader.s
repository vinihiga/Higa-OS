extern kernel_main              ; Signs that we have an external function

global loader                   ; the entry symbol for ELF
global irq_dummy                ; the generic IRQ
global irq_handle_keyboard      ; the IRQ for handling the keyboard

; GRUB STUFF...
MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 16384     ; size of stack in bytes, in this case 16KB

; The loader definition starts here
section .data
    global last_scancode
    last_scancode db 0

section .bss
align 4
stack_bottom:                   ; label points to beginning of memory
  resb KERNEL_STACK_SIZE        ; reserve stack for the kernel

stack_top:                      ; label points to the end of memory
section .multiboot              
align 4
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

section .text                   ; start of the text (code) section
loader:                         ; the loader label (defined as entry point in linker script)
    mov esp, stack_top
    call kernel_main
.loop:
    jmp .loop

; IRQS STUFF...

irq_dummy:
    push eax
    mov al, 0x20
    out 0x20, al                ; Just signs to PIC we have finished the event
    pop eax
    iretd

irq_handle_keyboard:
    push eax
    in al, 0x60
    mov [last_scancode], al
    mov al, 0x20
    out 0x20, al
    pop eax
    iretd
