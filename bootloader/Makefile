CROSS_COMPILE ?= arm-none-eabi

COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 

boot.bin : boot.s memmap
	$(CROSS_COMPILE)-as boot.s -o boot.o
	$(CROSS_COMPILE)-ld boot.o -o boot.elf
	$(CROSS_COMPILE)-objcopy boot.elf -O binary boot.bin
	qemu-system-aarch64 -M versatilepb -m 128M -kernel boot.bin
