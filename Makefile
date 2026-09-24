CC = gcc
SC_CFLAGS = -Ipayload/include -Os -fomit-frame-pointer -fno-asynchronous-unwind-tables
SC_CFLAGS += -ffunction-sections -fdata-sections
SC_CFLAGS += -fPIC -ffreestanding -fno-stack-protector -fno-zero-initialized-in-bss
SC_LDFLAGS = -nostdlib -static -Wl,-T,linker.ld -Wl,--gc-sections

SC_SRCDIR = payload/source
SC_OBJDIR = build/obj/shellcode
LOADER_SRCDIR = loader
LOADER_OBJDIR = build/obj/loader
BINDIR = build/bin

SC_SRCS := $(wildcard $(SC_SRCDIR)/*.c)
SC_OBJS := $(SC_SRCS:$(SC_SRCDIR)/%.c=$(SC_OBJDIR)/%.o)
LOADER_SRCS := $(wildcard $(LOADER_SRCDIR)/*.c)
LOADER_OBJS := $(LOADER_SRCS:$(LOADER_SRCDIR)/%.c=$(LOADER_OBJDIR)/%.o)

SC_ELF := $(BINDIR)/shellcode.elf
SC_BIN := $(BINDIR)/shellcode.bin
LOADER_BIN := $(BINDIR)/loader

all: $(SC_BIN) $(LOADER_BIN)

$(SC_BIN): $(SC_ELF)
	objcopy -O binary --only-section=.sc $(SC_ELF) $(SC_BIN)

$(SC_ELF): $(SC_OBJS) | $(BINDIR)
	$(CC) $(SC_LDFLAGS) -o $@ $(SC_OBJS)

$(SC_OBJDIR)/%.o: $(SC_SRCDIR)/%.c | $(SC_OBJDIR)
	$(CC) $(SC_CFLAGS) -c $< -o $@

$(LOADER_BIN): $(LOADER_OBJS) | $(BINDIR)
	$(CC) -o $@ $(LOADER_OBJS)

$(LOADER_OBJDIR)/%.o: $(LOADER_SRCDIR)/%.c | $(LOADER_OBJDIR)
	$(CC) -c $< -o $@
	
$(BINDIR) $(SC_OBJDIR) $(LOADER_OBJDIR):
	mkdir -p $@
	

clean:
	rm -rf build

.PHONY: all clean
