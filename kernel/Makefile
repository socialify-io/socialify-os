
kernel.bin : 
	/usr/local/bin/nasm -f elf64 boot.S 
	/usr/local/bin/nasm -f elf64 kernel.S 
	x86_64-unknown-linux-gnu-ld -n -o kernel.bin -T linker.ld boot.o kernel.o
	qemu-system-x86_64 kernel.bin
