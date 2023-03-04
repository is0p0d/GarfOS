run: install
	qemu-system-i386 -drive format=raw,file=a.img,if=floppy

floppyrun: install
	qemu-system-i386 -drive format=raw,file=/dev/sdc,if=floppy

debug: install
	qemu-system-i386 -S -s -drive format=raw,file=a.img,if=floppy & 
	ddd --debugger 'gdb -ex "target remote localhost:1234" -ex "break main" -ex "continue"' kernel.elf

debugHeadless: install 
	qemu-system-i386 -S -s -drive format=raw,file=a.img,if=floppy

physinstall: boot1 boot2
	dd if=/dev/zero of=/dev/sdc bs=512 count=2880 status=progress
	/sbin/mkdosfs /dev/sdc
	dd if=boot1 of=/dev/sdc bs=1 count=512 conv=notrunc status=progress
	mcopy -o boot2 b:BOOT2

install: boot1 boot2
	dd if=/dev/zero of=a.img bs=512 count=2880
	/sbin/mkdosfs a.img
	dd if=boot1 of=a.img bs=1 count=512 conv=notrunc
	mcopy -o boot2 a:BOOT2

boot2: kernel.elf
	objcopy -j .text* -j .data* -j .rodata* -S -O binary kernel.elf boot2

boot1: kernel.elf boot1.asm
	nasm -DENTRY=0x$(shell nm kernel.elf | grep main | cut -d " " -f 1) boot1.asm

kernel.elf: kernel_c.o kernel_asm.o kernel_kbd.o kernel_pic.o kernel_idt.o kernel_pcb.o usr_game.o processes.o screenutils.o buddy.o convert.o
	ld -g -melf_i386 -Ttext 0x10000 -e main -o kernel.elf kernel_c.o kernel_asm.o kernel_kbd.o kernel_pic.o kernel_idt.o kernel_pcb.o usr_game.o processes.o screenutils.o buddy.o convert.o

kernel_c.o: kernel.c io.h
	gcc -g -m32 -fno-stack-protector -c -o kernel_c.o kernel.c

kernel_asm.o: kernel.asm
	nasm -g -f elf -F dwarf -o kernel_asm.o kernel.asm

kernel_kbd.o: kernel_kbd.c kernel_kbd.h
	gcc -g -m32 -fno-stack-protector -c -o kernel_kbd.o kernel_kbd.c
kernel_pic.o: kernel_pic.c kernel_pic.h
	gcc -g -m32 -fno-stack-protector -c -o kernel_pic.o kernel_pic.c

kernel_idt.o: kernel_idt.c kernel_idt.h
	gcc -g -m32 -fno-stack-protector -c -o kernel_idt.o kernel_idt.c

kernel_pcb.o: kernel_pcb.c kernel_pcb.h
	gcc -g -m32 -fno-stack-protector -c -o kernel_pcb.o kernel_pcb.c

usr_game.o: usr_game.c usr_game.h
	gcc -g -m32 -fno-stack-protector -c -o usr_game.o usr_game.c

processes.o: processes.c processes.h
	gcc -g -m32 -fno-stack-protector -c -o processes.o processes.c

screenutils.o: screenutils.c screenutils.h
	gcc -g -m32 -fno-stack-protector -c -o screenutils.o screenutils.c

buddy.o: buddy.c buddy.h
	gcc -g -m32 -fno-stack-protector -c -o buddy.o buddy.c

convert.o: convert.c convert.h
	gcc -g -m32 -fno-stack-protector -c -o convert.o convert.c

clean:
	rm *.o
	rm *.img
	rm *.elf
	rm boot1 
	rm boot2

