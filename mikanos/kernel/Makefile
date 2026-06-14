TARGET = kernel.elf
OBJS = main.o graphics.o font.o console.o logger.o mouse.o pci.o interrupt.o\
       usb/memory.o usb/device.o \
       usb/classdriver/base.o usb/classdriver/hid.o \
       usb/classdriver/keyboard.o usb/classdriver/mouse.o \
       usb/xhci/device.o usb/xhci/devmgr.o usb/xhci/port.o \
       usb/xhci/registers.o usb/xhci/ring.o usb/xhci/trb.o \
       usb/xhci/xhci.o \
       asmfunc.o hankaku.o newlib_support.o
CPPFLAGS += -I.

CXXFLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
            -fno-exceptions -fno-rtti -std=c++17
LDFLAGS += --entry KernelMain -z norelro --image-base 0x100000 --static

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -f *.o *.bin kernel.elf usb/*.o usb/classdriver/*.o usb/xhci/*.o

kernel.elf: $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS) -lc -lc++ -lc++abi -lm


%.o: %.cpp Makefile
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.o: %.c Makefile
	clang $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.asm Makefile
	nasm -f elf64 -o $@ $<

hankaku.bin: hankaku.txt
	../tools/makefont.py -o hankaku.bin hankaku.txt

hankaku.o: hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 hankaku.bin hankaku.o
