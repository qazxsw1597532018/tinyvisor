default: all
.PHONY: all clean

include uefi/Uefi.mk
include tinyvisor/Tinyvisor.mk

CC = clang
LD = clang
AR = llvm-ar

COMMON_CFLAGS := \
	-target x86_64-unknown-windows \
	-ffreestanding \
    -fshort-wchar \
    -nostdinc \
    -nostdlib \
    -std=c11 \
    -static \
    -Wall \
    -Werror \
    -O1 \
    -flto

UEFILIB_CFLAGS := \
	$(COMMON_CFLAGS) \
    -g

TINYVISOR_CFLAGS := \
	$(UEFILIB_CFLAGS) \
    -Iuefi

TINYVISOR_LDFLAGS := \
	-target x86_64-unknown-windows \
	-nostdlib \
    -Wl,-entry:EfiMain \
    -Wl,-subsystem:efi_runtime_driver \
    -Wl,-debug \
    -fuse-ld=lld-link \
    -Lbin/$(TARGET) \
    -static -luefi

TINYVISOR_SFLAGS = \
	$(COMMON_CFLAGS) \
	-masm=intel

all: tinyvisor esp esp-img
tinyvisor: bin/tinyvisor.efi
uefilib: bin/uefi.lib
esp: bin/esp
esp-img: bin/esp.img

clean:
	mkdir -p bin obj
	rm -r bin obj

bin/tinyvisor.efi: $(TINYVISOR_OBJS) bin/uefi.lib
	@echo LD $@
	@mkdir -p $(@D)
	@$(LD) $(TINYVISOR_LDFLAGS) -o $@ $^

obj/tinyvisor/%.c.o: tinyvisor/%.c
	@echo CC $@
	@mkdir -p $(@D)
	@$(CC) $(TINYVISOR_CFLAGS) -c -o $@ $<

obj/tinyvisor/%.S.o: tinyvisor/%.S
	@echo CC $@
	@mkdir -p $(@D)
	@$(CC) $(TINYVISOR_SFLAGS) -c -o $@ $<

obj/uefi/%.c.o: uefi/%.c
	@echo CC $@
	@mkdir -p $(@D)
	@$(CC) $(UEFILIB_CFLAGS) -c -o $@ $<

bin/uefi.lib: $(UEFILIB_OBJS)
	@echo AR $@
	@mkdir -p $(@D)
	@$(AR) rcs $@ $^

bin/esp: bin/tinyvisor.efi
	@echo GEN $@
	@mkdir -p $@/EFI
	@cp $(word 1, $^) $@/EFI

bin/esp.img: bin/tinyvisor.efi
	@echo GEN $@
	@dd if=/dev/zero of=$@ bs=1k count=1440
	@mformat -i $@ -f 1440 ::
	@mmd -i $@ ::/EFI
	@mcopy -i $@ $(word 1, $^) ::/EFI/tinyvisor.efi
