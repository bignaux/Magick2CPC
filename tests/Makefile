CC=zcc
# zcc +cpc -v -lcpcfs -lm -create-app -subtype=dsk z88dk-putsprite.c -o z88dk-putsprite.dsk
CFLAGS=+cpc -v -lcpcfs -lm -create-app
EMULATOR=cap32

all: test.dsk

run: test.dsk
	$(EMULATOR) -a 'run"nixos.cpc' $^

# TODO
test.dsk: z88dk-cpc_PutSp.cpc z88dk-putsprite.cpc
	#iDSK $@ -n -i -t 1 $^
	#appmake +cpc --disk  -b $@ -c $^ --org 4608
	iDSK test.dsk  -n  -i z88dk-cpc_PutSp.cpc z88dk-putsprite.cpc  -e 1200 -c 1200 -t 1

# TODO: fix in sources
# source https://www.peppercarrot.com/0_sources/0ther/artworks/hi-res/2019-02-27_Flight-of-Spring_by-David-Revoy.jpg
z88dk-cpc_PutSp.h: peppercarrot.png
	../src/magick2cpc -c $^ | sed 's/peppercarrot.png/nixos/' >> $@

z88dk-cpc_PutSp.cpc: z88dk-cpc_PutSp.c z88dk-cpc_PutSp.h
	$(CC) $(CFLAGS) $< -o $@

# source https://www.peppercarrot.com/0_sources/0ther/artworks/hi-res/2018-11-28_coc_by-David-Revoy.jpg
# limite by uncrustify : #define AL_SIZE 8000
z88dk-putsprite.h: coc.png
	../src/magick2cpc -z $^ -o $@
	uncrustify -c uncrustify-c-cpp.cfg --replace z88dk-putsprite.h

z88dk-putsprite.cpc: z88dk-putsprite.c z88dk-putsprite.h
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean run

clean:
	@rm -f *.wav *.dsk *.cpc *.bin *.h zcc_opt.def screenshot_* *~