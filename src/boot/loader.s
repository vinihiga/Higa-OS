extern kernel_main              ; Signs that we have an external function

global loader                   ; the entry symbol for ELF
global irq_dummy                ; the generic IRQ
global irq_handle_keyboard      ; the IRQ for handling the keyboard

; GRUB STUFF...
MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes, in this case 4KB

; The loader definition starts here
section .data
    global idt_last_scancode
    idt_last_scancode db 0

    global idt_is_left_shift_pressed
    idt_is_left_shift_pressed db 0

section .bss
    align 4
    stack_bottom:                   ; label points to beginning of memory
    resb KERNEL_STACK_SIZE          ; reserve stack for the kernel

    stack_top:                      ; label points to the end of memory

section .multiboot              
    align 4
    dd MAGIC_NUMBER                 ; write the magic number to the machine code,
    dd FLAGS                        ; the flags,
    dd CHECKSUM                     ; and the checksum

section .text                       ; start of the text (code) section
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

        ; Checks if we are going to have 2 bytes of data for extended keycode,
        ; otherwise we won't jump and we are going to show a regular input with just 1 byte of info.
        cmp al, 0x2A
        je .is_special_key_pressed
        cmp al, 0xAA
        je .is_special_key_released

        jmp irq_handle_keyboard.get_scan_code

    .is_special_key_pressed:
        mov byte [idt_is_left_shift_pressed], 1
        jmp .finish

    .is_special_key_released:
        mov byte [idt_is_left_shift_pressed], 0
        jmp .finish
    
    .get_scan_code:
        mov byte [idt_last_scancode], al
        jmp .finish
    
    .finish:
        mov al, 0x20
        out 0x20, al
        pop eax
        iretd
