C_FILES = $(wildcard src/*.c)
OBJS = $(wildcard build/*.o)

run: build
	cp ./build/bin/kernel.elf ./iso/boot/ 
	mkisofs -R -b boot/grub/stage2_eltorito \
		-no-emul-boot -boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso iso
	bochs -f bochsrc.txt -q

build: assembly compile link

link:
	i686-elf-ld -T link.ld $(OBJS) -o ./build/bin/kernel.elf

compile:
	i686-elf-gcc -m32 -O0 -ffreestanding -nostdlib \
		-Wall -Wextra -Werror -I ./src/includes/ -c $(C_FILES)
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