#include "./includes/keyboard.h"

static const unsigned char KB_MAP[128] = {
  0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s',
  'd','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static const unsigned char KB_MAP_SHIFTED[128] = {
  0,27,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t',
  'Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,'A','S',
  'D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

char kb_get_scan_code() {
  unsigned char scancode;

  while (1) {
    idt_last_scancode = 0;
    while (idt_last_scancode == 0);

    scancode = idt_last_scancode;
    idt_last_scancode = 0;
    int is_key_released = scancode & 0x80;

    if (!is_key_released) {
      break;
    }
  }

  if (idt_is_left_shift_pressed) {
    return KB_MAP_SHIFTED[scancode];
  }

  return KB_MAP[scancode];
}