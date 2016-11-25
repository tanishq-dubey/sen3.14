CC = gcc

CFLAGS = -Wall -g -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE

LIBS = -L/usr/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

MAIN = nes

.PHONY: depend clean

all:    $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) mem_dump.bin

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

cpu.o: cpu.h main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
cpu.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
cpu.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
cpu.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
cpu.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
cpu.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
cpu.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
cpu.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
cpu.o: /usr/include/sys/_types/_intptr_t.h
cpu.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
cpu.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
cpu.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
cpu.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
cpu.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
cpu.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
cpu.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
cpu.o: /usr/include/secure/_common.h /usr/include/string.h
cpu.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
cpu.o: /usr/include/strings.h /usr/include/secure/_string.h
cpu.o: /usr/include/stdlib.h /usr/include/sys/wait.h
cpu.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
cpu.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
cpu.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
cpu.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
cpu.o: /usr/include/mach/i386/_structs.h
cpu.o: /usr/include/sys/_pthread/_pthread_attr_t.h
cpu.o: /usr/include/sys/_types/_sigaltstack.h
cpu.o: /usr/include/sys/_types/_ucontext.h
cpu.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
cpu.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
cpu.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
cpu.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
cpu.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
cpu.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
cpu.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
cpu.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
cpu.o: /usr/include/sys/_types/_u_int16_t.h
cpu.o: /usr/include/sys/_types/_u_int32_t.h
cpu.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
cpu.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
cpu.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h mmc.h
cpu.o: mmc2.h mmc1.h
game.o: game.h main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
game.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
game.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
game.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
game.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
game.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
game.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
game.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
game.o: /usr/include/sys/_types/_intptr_t.h
game.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
game.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
game.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
game.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
game.o: /usr/include/secure/_common.h /usr/include/string.h
game.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
game.o: /usr/include/strings.h /usr/include/secure/_string.h
game.o: /usr/include/stdlib.h /usr/include/sys/wait.h
game.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
game.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
game.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
game.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
game.o: /usr/include/mach/i386/_structs.h
game.o: /usr/include/sys/_pthread/_pthread_attr_t.h
game.o: /usr/include/sys/_types/_sigaltstack.h
game.o: /usr/include/sys/_types/_ucontext.h
game.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
game.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
game.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
game.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
game.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
game.o: /usr/include/sys/_types/_ct_rune_t.h
game.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
game.o: /usr/include/machine/types.h /usr/include/i386/types.h
game.o: /usr/include/sys/_types/_u_int8_t.h
game.o: /usr/include/sys/_types/_u_int16_t.h
game.o: /usr/include/sys/_types/_u_int32_t.h
game.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
game.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
game.o: /usr/include/sys/_pthread/_pthread_t.h memory.h ppu.h cpu.h mmc.h
game.o: mmc2.h mmc1.h
main.o: main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
main.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
main.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
main.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
main.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
main.o: /usr/include/sys/_types/_intptr_t.h
main.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
main.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
main.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
main.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
main.o: /usr/include/secure/_common.h /usr/include/string.h
main.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
main.o: /usr/include/strings.h /usr/include/secure/_string.h
main.o: /usr/include/stdlib.h /usr/include/sys/wait.h
main.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
main.o: /usr/include/mach/i386/_structs.h
main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
main.o: /usr/include/sys/_types/_sigaltstack.h
main.o: /usr/include/sys/_types/_ucontext.h
main.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
main.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
main.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
main.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/sys/_types/_ct_rune_t.h
main.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/sys/_types/_u_int8_t.h
main.o: /usr/include/sys/_types/_u_int16_t.h
main.o: /usr/include/sys/_types/_u_int32_t.h
main.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
main.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
main.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h cpu.h
main.o: mmc.h mmc2.h mmc1.h
memory.o: memory.h /usr/include/strings.h /usr/include/_types.h
memory.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
memory.o: /usr/include/sys/_symbol_aliasing.h
memory.o: /usr/include/sys/_posix_availability.h
memory.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
memory.o: /usr/include/sys/_pthread/_pthread_types.h
memory.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
memory.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
memory.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_rsize_t.h
memory.o: /usr/include/sys/_types/_errno_t.h
memory.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
memory.o: /usr/include/secure/_common.h game.h main.h /usr/include/stdint.h
memory.o: /usr/include/sys/_types/_int8_t.h
memory.o: /usr/include/sys/_types/_int16_t.h
memory.o: /usr/include/sys/_types/_int32_t.h
memory.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
memory.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
memory.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
memory.o: /usr/include/sys/_types/_uintptr_t.h
memory.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
memory.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
memory.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
memory.o: /usr/include/secure/_stdio.h /usr/include/stdlib.h
memory.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
memory.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
memory.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
memory.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
memory.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
memory.o: /usr/include/sys/_pthread/_pthread_attr_t.h
memory.o: /usr/include/sys/_types/_sigaltstack.h
memory.o: /usr/include/sys/_types/_ucontext.h
memory.o: /usr/include/sys/_types/_sigset_t.h
memory.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
memory.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
memory.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
memory.o: /usr/include/libkern/_OSByteOrder.h
memory.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
memory.o: /usr/include/sys/_types/_ct_rune_t.h
memory.o: /usr/include/sys/_types/_rune_t.h
memory.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
memory.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
memory.o: /usr/include/sys/_types/_u_int16_t.h
memory.o: /usr/include/sys/_types/_u_int32_t.h
memory.o: /usr/include/sys/_types/_u_int64_t.h
memory.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
memory.o: /usr/include/signal.h /usr/include/sys/_pthread/_pthread_t.h ppu.h
memory.o: cpu.h mmc.h mmc2.h mmc1.h
mmc.o: mmc.h main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
mmc.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
mmc.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
mmc.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
mmc.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
mmc.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
mmc.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
mmc.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
mmc.o: /usr/include/sys/_types/_intptr_t.h
mmc.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
mmc.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
mmc.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
mmc.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
mmc.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
mmc.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
mmc.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
mmc.o: /usr/include/secure/_common.h /usr/include/string.h
mmc.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
mmc.o: /usr/include/strings.h /usr/include/secure/_string.h
mmc.o: /usr/include/stdlib.h /usr/include/sys/wait.h
mmc.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
mmc.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mmc.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mmc.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
mmc.o: /usr/include/mach/i386/_structs.h
mmc.o: /usr/include/sys/_pthread/_pthread_attr_t.h
mmc.o: /usr/include/sys/_types/_sigaltstack.h
mmc.o: /usr/include/sys/_types/_ucontext.h
mmc.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
mmc.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
mmc.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mmc.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mmc.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mmc.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
mmc.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
mmc.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
mmc.o: /usr/include/sys/_types/_u_int16_t.h
mmc.o: /usr/include/sys/_types/_u_int32_t.h
mmc.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
mmc.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
mmc.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h cpu.h
mmc.o: mmc2.h mmc1.h
mmc1.o: mmc1.h main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
mmc1.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
mmc1.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
mmc1.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
mmc1.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
mmc1.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
mmc1.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
mmc1.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
mmc1.o: /usr/include/sys/_types/_intptr_t.h
mmc1.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
mmc1.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
mmc1.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
mmc1.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
mmc1.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
mmc1.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
mmc1.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
mmc1.o: /usr/include/secure/_common.h /usr/include/string.h
mmc1.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
mmc1.o: /usr/include/strings.h /usr/include/secure/_string.h
mmc1.o: /usr/include/stdlib.h /usr/include/sys/wait.h
mmc1.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
mmc1.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mmc1.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mmc1.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
mmc1.o: /usr/include/mach/i386/_structs.h
mmc1.o: /usr/include/sys/_pthread/_pthread_attr_t.h
mmc1.o: /usr/include/sys/_types/_sigaltstack.h
mmc1.o: /usr/include/sys/_types/_ucontext.h
mmc1.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
mmc1.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
mmc1.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mmc1.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mmc1.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mmc1.o: /usr/include/sys/_types/_ct_rune_t.h
mmc1.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
mmc1.o: /usr/include/machine/types.h /usr/include/i386/types.h
mmc1.o: /usr/include/sys/_types/_u_int8_t.h
mmc1.o: /usr/include/sys/_types/_u_int16_t.h
mmc1.o: /usr/include/sys/_types/_u_int32_t.h
mmc1.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
mmc1.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
mmc1.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h cpu.h
mmc1.o: mmc.h mmc2.h
mmc2.o: mmc2.h main.h /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
mmc2.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
mmc2.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
mmc2.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
mmc2.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
mmc2.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
mmc2.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
mmc2.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
mmc2.o: /usr/include/sys/_types/_intptr_t.h
mmc2.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
mmc2.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
mmc2.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
mmc2.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
mmc2.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
mmc2.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
mmc2.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
mmc2.o: /usr/include/secure/_common.h /usr/include/string.h
mmc2.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
mmc2.o: /usr/include/strings.h /usr/include/secure/_string.h
mmc2.o: /usr/include/stdlib.h /usr/include/sys/wait.h
mmc2.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
mmc2.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mmc2.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mmc2.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
mmc2.o: /usr/include/mach/i386/_structs.h
mmc2.o: /usr/include/sys/_pthread/_pthread_attr_t.h
mmc2.o: /usr/include/sys/_types/_sigaltstack.h
mmc2.o: /usr/include/sys/_types/_ucontext.h
mmc2.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
mmc2.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
mmc2.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mmc2.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mmc2.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mmc2.o: /usr/include/sys/_types/_ct_rune_t.h
mmc2.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
mmc2.o: /usr/include/machine/types.h /usr/include/i386/types.h
mmc2.o: /usr/include/sys/_types/_u_int8_t.h
mmc2.o: /usr/include/sys/_types/_u_int16_t.h
mmc2.o: /usr/include/sys/_types/_u_int32_t.h
mmc2.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
mmc2.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
mmc2.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h cpu.h
mmc2.o: mmc.h mmc1.h
ppu.o: ppu.h game.h main.h /usr/include/stdint.h
ppu.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
ppu.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
ppu.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
ppu.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
ppu.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
ppu.o: /usr/include/sys/_symbol_aliasing.h
ppu.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
ppu.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
ppu.o: /usr/include/sys/_types/_intptr_t.h
ppu.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
ppu.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
ppu.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
ppu.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
ppu.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
ppu.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
ppu.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
ppu.o: /usr/include/secure/_common.h /usr/include/string.h
ppu.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
ppu.o: /usr/include/strings.h /usr/include/secure/_string.h
ppu.o: /usr/include/stdlib.h /usr/include/sys/wait.h
ppu.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
ppu.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
ppu.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
ppu.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
ppu.o: /usr/include/mach/i386/_structs.h
ppu.o: /usr/include/sys/_pthread/_pthread_attr_t.h
ppu.o: /usr/include/sys/_types/_sigaltstack.h
ppu.o: /usr/include/sys/_types/_ucontext.h
ppu.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
ppu.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
ppu.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
ppu.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
ppu.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
ppu.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
ppu.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
ppu.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
ppu.o: /usr/include/sys/_types/_u_int16_t.h
ppu.o: /usr/include/sys/_types/_u_int32_t.h
ppu.o: /usr/include/sys/_types/_u_int64_t.h /usr/include/sys/_types/_dev_t.h
ppu.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
ppu.o: /usr/include/sys/_pthread/_pthread_t.h memory.h cpu.h mmc.h mmc2.h
ppu.o: mmc1.h
sdl_render.o: sdl_render.h main.h /usr/include/stdint.h
sdl_render.o: /usr/include/sys/_types/_int8_t.h
sdl_render.o: /usr/include/sys/_types/_int16_t.h
sdl_render.o: /usr/include/sys/_types/_int32_t.h
sdl_render.o: /usr/include/sys/_types/_int64_t.h
sdl_render.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
sdl_render.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
sdl_render.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
sdl_render.o: /usr/include/sys/_symbol_aliasing.h
sdl_render.o: /usr/include/sys/_posix_availability.h
sdl_render.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
sdl_render.o: /usr/include/sys/_pthread/_pthread_types.h
sdl_render.o: /usr/include/sys/_types/_intptr_t.h
sdl_render.o: /usr/include/sys/_types/_uintptr_t.h
sdl_render.o: /usr/include/_types/_intmax_t.h
sdl_render.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
sdl_render.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
sdl_render.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
sdl_render.o: /usr/include/sys/_types/_size_t.h
sdl_render.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
sdl_render.o: /usr/include/sys/_types/_off_t.h
sdl_render.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
sdl_render.o: /usr/include/secure/_common.h /usr/include/string.h
sdl_render.o: /usr/include/sys/_types/_rsize_t.h
sdl_render.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
sdl_render.o: /usr/include/secure/_string.h /usr/include/stdlib.h
sdl_render.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
sdl_render.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
sdl_render.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
sdl_render.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
sdl_render.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
sdl_render.o: /usr/include/sys/_pthread/_pthread_attr_t.h
sdl_render.o: /usr/include/sys/_types/_sigaltstack.h
sdl_render.o: /usr/include/sys/_types/_ucontext.h
sdl_render.o: /usr/include/sys/_types/_sigset_t.h
sdl_render.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
sdl_render.o: /usr/include/sys/_types/_timeval.h
sdl_render.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
sdl_render.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
sdl_render.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
sdl_render.o: /usr/include/sys/_types/_ct_rune_t.h
sdl_render.o: /usr/include/sys/_types/_rune_t.h
sdl_render.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
sdl_render.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
sdl_render.o: /usr/include/sys/_types/_u_int16_t.h
sdl_render.o: /usr/include/sys/_types/_u_int32_t.h
sdl_render.o: /usr/include/sys/_types/_u_int64_t.h
sdl_render.o: /usr/include/sys/_types/_dev_t.h
sdl_render.o: /usr/include/sys/_types/_mode_t.h /usr/include/signal.h
sdl_render.o: /usr/include/sys/_pthread/_pthread_t.h game.h memory.h ppu.h
sdl_render.o: cpu.h mmc.h mmc2.h mmc1.h
