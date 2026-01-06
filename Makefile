C_FILES = $(wildcard src/*.c)
OBJS = $(wildcard build/*.o)

ifeq ($(shell uname -s), Linux)
	COMPILER = gcc
	LINKER = ld -m elf_i386
else
	COMPILER = i686-elf-gcc
	LINKER = i686-elf-ld
endif

run: build
	cp ./build/bin/kernel.elf ./iso/boot/ 
	mkisofs -R -b boot/grub/stage2_eltorito \
		-no-emul-boot -boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso iso
	qemu-system-i386 -cdrom os.iso

build: assembly compile link

link:
	$(LINKER) -T link.ld $(OBJS) -o ./build/bin/kernel.elf

compile:
	$(COMPILER) -m32 -O0 -ffreestanding -nostdlib -Wall -Wextra -Werror -Wno-unused -I ./src/includes/ -c $(C_FILES)
	mv *.o build/

assembly:
	nasm -f elf32 ./src/boot/loader.s -o ./build/loader.o

setup: clean
	mkdir build
	mkdir build/bin

clean:
	rm os.iso
	rm -rf build/
	rm *.o