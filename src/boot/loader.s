extern kernel_main              ; Signs that we have an external function

global loader                   ; the entry symbol for ELF

; GRUB STUFF...
MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 16384     ; size of stack in bytes, in this case 16KB

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
