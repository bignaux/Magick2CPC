/*
	../src/magick2cpc -c triskel.png -o triskel.h
	zcc +cpc -v -lndos -subtype=dsk -create-app triskel.c -o triskel
	cap32 -a 'run"triskel.cpc' triskel.dsk
 */

#include <cpc.h>
#include <stdio.h>

extern unsigned char triskel[];
extern unsigned char tintas[];

struct Sprite {
	unsigned char height;
	unsigned char width;
	unsigned char *buffer;
};

#asm
._triskel
defb $00,$00,$00,$00,$00,$40,$C0,$C0,$80,$00,$00,$00,$00,$00
defb $00,$00,$00,$00,$00,$40,$C0,$C0,$80,$00,$00,$00,$00,$00
defb $00,$00,$00,$00,$C0,$C0,$C0,$C0,$C0,$C0,$00,$00,$00,$00
defb $00,$00,$00,$00,$C0,$C0,$C0,$C0,$C0,$C0,$00,$00,$00,$00
defb $00,$00,$00,$C0,$80,$00,$00,$00,$00,$40,$C0,$00,$00,$00
defb $00,$00,$00,$C0,$80,$00,$00,$00,$00,$40,$C0,$00,$00,$00
defb $00,$00,$40,$80,$00,$00,$04,$0C,$00,$00,$40,$80,$00,$00
defb $00,$00,$40,$80,$00,$00,$04,$0C,$00,$00,$40,$80,$00,$00
defb $00,$00,$C0,$00,$00,$04,$0C,$0C,$08,$00,$00,$C0,$00,$00
defb $00,$00,$C0,$00,$00,$04,$0C,$0C,$08,$00,$00,$C0,$00,$00
defb $00,$40,$80,$00,$00,$0C,$08,$00,$0C,$00,$00,$40,$80,$00
defb $00,$40,$80,$00,$00,$0C,$08,$00,$0C,$00,$00,$40,$80,$00
defb $00,$C0,$00,$00,$00,$0C,$00,$00,$04,$08,$00,$00,$C0,$00
defb $00,$C0,$00,$00,$00,$0C,$00,$00,$04,$08,$00,$00,$C0,$00
defb $00,$80,$00,$00,$00,$0C,$04,$08,$04,$08,$00,$00,$40,$00
defb $00,$80,$00,$00,$00,$0C,$04,$08,$04,$08,$00,$00,$40,$00
defb $40,$80,$00,$00,$00,$0C,$00,$0C,$04,$08,$00,$00,$40,$80
defb $40,$80,$00,$00,$00,$0C,$04,$0C,$04,$08,$00,$00,$40,$80
defb $40,$00,$00,$00,$00,$0C,$0C,$08,$04,$08,$00,$00,$00,$80
defb $40,$00,$00,$00,$00,$0C,$0C,$08,$04,$08,$00,$00,$00,$80
defb $40,$00,$00,$00,$00,$00,$0C,$00,$04,$08,$00,$00,$00,$80
defb $40,$00,$00,$00,$00,$00,$0C,$00,$04,$08,$00,$00,$00,$80
defb $C0,$00,$00,$00,$00,$00,$00,$00,$0C,$00,$00,$00,$00,$C0
defb $C0,$00,$00,$00,$00,$00,$00,$00,$0C,$00,$00,$00,$00,$C0
defb $C0,$00,$00,$04,$0C,$0C,$00,$0C,$0C,$00,$00,$00,$00,$C0
defb $C0,$00,$00,$04,$0C,$0C,$00,$0C,$0C,$00,$00,$00,$00,$C0
defb $C0,$00,$04,$0C,$0C,$0C,$0C,$0C,$08,$00,$00,$00,$00,$C0
defb $C0,$00,$04,$0C,$0C,$0C,$0C,$0C,$08,$00,$00,$00,$00,$C0
defb $C0,$00,$04,$08,$00,$04,$0C,$0C,$00,$0C,$0C,$08,$00,$C0
defb $C0,$00,$04,$08,$00,$04,$0C,$0C,$00,$0C,$0C,$08,$00,$C0
defb $C0,$00,$0C,$00,$00,$00,$04,$0C,$00,$0C,$0C,$0C,$00,$C0
defb $C0,$00,$0C,$00,$00,$00,$04,$0C,$00,$0C,$0C,$0C,$00,$C0
defb $C0,$00,$0C,$00,$0C,$08,$04,$08,$04,$0C,$00,$0C,$00,$C0
defb $C0,$00,$0C,$00,$0C,$08,$04,$08,$04,$0C,$00,$0C,$00,$C0
defb $40,$00,$08,$04,$0C,$0C,$00,$0C,$04,$0C,$08,$0C,$00,$80
defb $40,$00,$08,$04,$0C,$0C,$00,$0C,$04,$0C,$08,$0C,$00,$80
defb $40,$00,$0C,$00,$00,$0C,$00,$0C,$00,$0C,$00,$0C,$00,$80
defb $40,$00,$0C,$00,$00,$0C,$00,$0C,$00,$0C,$00,$0C,$00,$80
defb $40,$80,$0C,$00,$00,$0C,$00,$0C,$08,$00,$00,$0C,$40,$80
defb $40,$80,$0C,$00,$00,$0C,$00,$0C,$08,$00,$00,$0C,$40,$80
defb $00,$80,$04,$0C,$0C,$08,$00,$04,$0C,$00,$0C,$08,$40,$00
defb $00,$80,$04,$0C,$0C,$08,$00,$04,$0C,$00,$0C,$08,$40,$00
defb $00,$C0,$00,$0C,$0C,$00,$00,$00,$0C,$0C,$0C,$00,$C0,$00
defb $00,$C0,$00,$0C,$0C,$00,$00,$00,$0C,$0C,$0C,$00,$C0,$00
defb $00,$40,$80,$00,$00,$00,$00,$00,$00,$0C,$00,$40,$80,$00
defb $00,$40,$80,$00,$00,$00,$00,$00,$00,$0C,$00,$40,$80,$00
defb $00,$00,$C0,$00,$00,$00,$00,$00,$00,$00,$00,$C0,$00,$00
defb $00,$00,$C0,$00,$00,$00,$00,$00,$00,$00,$00,$C0,$00,$00
defb $00,$00,$40,$80,$00,$00,$00,$00,$00,$00,$40,$80,$00,$00
defb $00,$00,$40,$80,$00,$00,$00,$00,$00,$00,$40,$80,$00,$00
defb $00,$00,$00,$C0,$80,$00,$00,$00,$00,$40,$C0,$00,$00,$00
defb $00,$00,$00,$C0,$80,$00,$00,$00,$00,$40,$C0,$00,$00,$00
defb $00,$00,$00,$00,$C0,$C0,$C0,$C0,$C0,$C0,$00,$00,$00,$00
defb $00,$00,$00,$00,$C0,$C0,$C0,$C0,$C0,$C0,$00,$00,$00,$00
defb $00,$00,$00,$00,$00,$40,$C0,$C0,$80,$00,$00,$00,$00,$00
defb $00,$00,$00,$00,$00,$40,$C0,$C0,$80,$00,$00,$00,$00,$00

._tintas
defb 0,6,26,28,28,28,28,28,28,28,28,28,28,28,28,99
#endasm

unsigned char swapNibbles(unsigned char x) 
{ 
    return ( (x & 0x0F)<<4 | (x & 0xF0)>>4 ); 
} 

unsigned char swapBitsInPair(unsigned char x) 
{ 
    // Extracting the high bit shift it to lowbit 
    // Extracting the low bit shift it to highbit 
    return ((x & 0b10101010) >> 1) |  
            ((x & 0b01010101) << 1);     
} 

mirrored(unsigned char * buffer, const unsigned char height , 
    const unsigned char width, const unsigned char ppb )
{
	unsigned char temp, *pbuffer = buffer;
	char w,h = 0;

	while ( h < height ) {
		while ( w < width / 2 ) {
			temp = swapBitsInPair(*(pbuffer+w));
			*(pbuffer+w) = swapBitsInPair(*(pbuffer+width - w -1));
			*(pbuffer+width - w -1) = temp;
			w++;
		}
		pbuffer += width;
		w = 0;
		h++;
	}
}

main()
{
	char w,h = 0;
	const char height = 56;
	const char width  = 14;
	int scr = 0xC000;

	unsigned char *buffer[14*56];
	memcpy(buffer,triskel,height*width);

	mirrored(buffer,height,width,2);
	cpc_DisableFirmware();
    cpc_SetMode(0);

    cpc_PutSp(buffer,height,width,scr);
    cpc_PutSpXOR(triskel,height,width,scr+width);  // cpc_PutSp(char *sprite, int height, int width, unsigned int address)

    while (!cpc_AnyKeyPressed()){}   
}
