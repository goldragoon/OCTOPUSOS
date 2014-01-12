################################################
# set rule for build
################################################

GCCDIRECTORY = /usr/cross/bin
NASM32 = nasm
GCC32 = $(GCCDIRECTORY)/x86_64-pc-linux-gcc -c -m32 -ffreestanding
LD32 = $(GCCDIRECTORY)/x86_64-pc-linux-ld -melf_i386 -T ../elf_i386.x -nostdlib -e Main -Ttext 0x10200
OBJCOPY32 = $(GCCDIRECTORY)/x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -S -O binary

OBJECTDIRECTORY = Temp
SOURCEDIRECTORY = SysSource 

################################################
# set build thing and how to build
################################################
all: prepare Kernel32.bin

prepare:
	mkdir -p $(OBJECTDIRECTORY)

$(OBJECTDIRECTORY)/entrypoint.bin: SysSource/entrypoint.asm
	$(NASM32) -o $@ $<

dep:
	@echo === Make Dependancy File ===
	make -C $(OBJECTDIRECTORY) -f ../makefile InternalDependancy
	@echo === Dependancy Search Complete ===

ExecuteInternalBuild: dep
	@echo ===ExecuteInternalBuild=====
	make -C $(OBJECTDIRECTORY) -f ../makefile Kernel32.elf

$(OBJECTDIRECTORY)/Kernel32.elf.bin: ExecuteInternalBuild
	$(OBJCOPY32) $(OBJECTDIRECTORY)/Kernel32.elf $@



Kernel32.bin: $(OBJECTDIRECTORY)/entrypoint.bin $(OBJECTDIRECTORY)/Kernel32.elf.bin
	cat $^ > $@

clean:
	rm -f *.bin
	rm -f $(OBJECTDIRECTORY)/*.*
	@echo ======== Clean Complete =========
###############################################
# Call for reMake...... for Temp Directory
###############################################

CENTRYPOINTOBJECTFILE = Main.o
CSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
ASSEMBLYSOURCEFILES = $(wildcard ../$(SOURCEDIRECTORY)/*.asm)
COBJECTFILES = $(subst Main.o, ,$(notdir $(patsubst %.c, %.o, $(CSOURCEFILES))))
ASSEMBLYOBJECTFILES = $(notdir $(patsubst %.asm, %.o, $(ASSEMBLYSOURCEFILES)))

%.o: $(SOURCEDIRECTORY)/%.c
	$(GCC32) -C $<

%.o: $(SOURCEDIRECTORY)/%.asm
	$(NASM32) -f elf32 -o $@ $<

InternalDependancy:
	$(GCC32) -MM $(CSOURCEFILES) > Dependancy.dep

Kernel32.elf: $(CENTRYPOINTOBJECTFILE) $(COBJECTFILES) $(ASSEMBLYOBJECTFILES)
	@echo === Kernel32.elf build ===
	$(LD32) -o $@ $^
	@echo ====== Build end =========


ifeq (Dependancy.dep, $(wildcard Dependancy.dep))
include Dependancy.dep
endif
