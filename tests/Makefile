CC=zcc
CFLAGS=+cpc -v -lcpcfs -lm -subtype=dsk -create-app
EMULATOR=cap32

all: nixos.dsk

run: nixos.dsk
	$(EMULATOR) -a 'run"nixos.cpc' $^

# need to be fixed in sources
nixos.h: nixos-logo-mode0.png
	../src/magick2cpc -c $^ -o $@
	#echo -e "extern uchar nixos[];\n""#asm\n" | cat - $@

nixos.dsk: nixos.c nixos.h
	$(CC) $(CFLAGS) $< -o $@

z88dk-putsprite.h: nixos-logo-mode2.png
	../src/magick2cpc -z $^ -o $@
	uncrustify -c uncrustify-c-cpp.cfg --replace z88dk-putsprite.h

z88dk-putsprite.dsk: z88dk-putsprite.c z88dk-putsprite.h
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean run

clean:
	@rm -f *.wav *.dsk *.cpc *.bin *.h