
# ../src/magick2cpc -b -z nixos-logo-b\&w.png -o nixos.h 

CC=zcc
CFLAGS=+cpc -v -lcpcfs -lm -subtype=dsk -create-app

all: nixos.dsk

nixos.dsk : nixos.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	@rm *.wav *.dsk *.cpc *.bin