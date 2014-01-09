all: BootLoader Disk.img

BootLoader:
	@echo
	@echo ========== Build BootLoader ==========
	@echo 

	make -C bootloader

	@echo
	@echo ========== Build Complete ============
	@echo
Kernel32:
	@echo 
	@echo =========== 32 kernel Build ==========
	@echo

	make -C kernel32
	
	@echo
	@echo =========== Build Complete ===========
	@echo


Disk.img : BootLoader Kernel32
	@echo 
	@echo =========== Diskimage Build ==========
	@echo

	cat bootloader/bootloader.bin kernel32/Kernel32.bin > Disk.img
	
	@echo
	@echo =========== All Build Complete =======
	@echo

clean:

	make -C bootloader clean
	make -C kernel32 clean
	rm -f Disk.img
