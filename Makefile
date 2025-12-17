run: assembly compile link
	cp ./build/bin/kernel.elf ./iso/boot/ 
	mkisofs -R -b boot/grub/stage2_eltorito \
		-no-emul-boot -boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso iso
	bochs -f bochsrc.txt -q

link:
	i686-elf-ld -T link.ld ./build/loader.o ./build/kmain.o -o ./build/bin/kernel.elf

compile:
	i686-elf-gcc -m32 -O0 -ffreestanding -nostdlib \
	-Wall -Wextra -Werror -c ./src/kmain.c -o ./build/kmain.o

assembly:
	nasm -f elf32 ./src/boot/loader.s -o ./build/loader.o

setup:
	mkdir build
	mkdir build/bin

clean:
	rm os.iso
	rm -rf build/