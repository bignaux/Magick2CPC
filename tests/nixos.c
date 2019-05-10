/*
    ../src/magick2cpc -c nixos-logo-mode0.png -o nixos.h
    zcc +cpc -v -lndos -subtype=dsk -create-app nixos.c -o nixos
    cap32 -a 'run"nixos.cpc' nixos.dsk
 */

#include <cpc.h>
#include <stdio.h>

extern unsigned char nixos[];
extern unsigned char tintas[];

struct Sprite {
    unsigned char height;
    unsigned char width;
    unsigned char *buffer;
};

#asm
._nixos
defb $00,$00,$00,$40,$48,$00,$00,$CC,$88,$00,$44,$00,$00,$00,$00                                                              
defb $00,$00,$00,$10,$48,$00,$00,$CC,$88,$00,$44,$88,$00,$00,$00                                                              
defb $00,$00,$00,$10,$18,$00,$00,$44,$88,$00,$CC,$88,$00,$00,$00                                                              
defb $00,$00,$00,$10,$18,$00,$00,$44,$CC,$00,$CC,$88,$00,$00,$00                                                              
defb $00,$00,$00,$10,$0C,$80,$00,$44,$CC,$00,$CC,$88,$00,$00,$00
defb $00,$00,$00,$40,$0C,$20,$00,$44,$CC,$44,$CC,$00,$00,$00,$00
defb $00,$00,$00,$00,$0C,$20,$00,$00,$CC,$CC,$CC,$00,$00,$00,$00
defb $00,$00,$00,$00,$24,$08,$00,$00,$CC,$CC,$CC,$00,$00,$00,$00
defb $00,$00,$00,$00,$84,$48,$00,$00,$CC,$CC,$CC,$00,$00,$00,$00
defb $00,$00,$00,$00,$84,$18,$00,$00,$44,$CC,$88,$00,$00,$00,$00
defb $00,$00,$90,$30,$24,$0C,$30,$30,$C4,$CC,$88,$00,$00,$00,$00
defb $00,$00,$24,$0C,$0C,$0C,$0C,$0C,$64,$CC,$88,$00,$10,$00,$00
defb $00,$00,$24,$0C,$0C,$0C,$0C,$0C,$64,$CC,$88,$00,$10,$00,$00
defb $00,$00,$0C,$0C,$0C,$0C,$0C,$0C,$30,$CC,$88,$00,$04,$00,$00
defb $00,$40,$0C,$0C,$0C,$0C,$0C,$0C,$18,$CC,$88,$00,$84,$80,$00
defb $00,$00,$30,$30,$24,$18,$30,$30,$60,$CC,$88,$00,$24,$20,$00
defb $00,$00,$00,$00,$64,$C8,$00,$00,$00,$44,$88,$00,$24,$20,$00
defb $00,$00,$00,$00,$CC,$88,$00,$00,$00,$44,$CC,$40,$0C,$20,$00
defb $00,$00,$00,$00,$CC,$88,$00,$00,$00,$44,$CC,$10,$0C,$80,$00
defb $00,$00,$00,$00,$CC,$88,$00,$00,$00,$44,$CC,$30,$0C,$00,$00
defb $00,$00,$00,$44,$CC,$00,$00,$00,$00,$00,$CC,$24,$18,$00,$00
defb $00,$00,$00,$44,$CC,$00,$00,$00,$00,$00,$CC,$24,$48,$00,$00
defb $00,$00,$00,$44,$CC,$00,$00,$00,$00,$00,$98,$24,$48,$00,$00
defb $44,$CC,$CC,$CC,$88,$00,$00,$00,$00,$00,$40,$24,$18,$30,$20
defb $44,$CC,$CC,$CC,$88,$00,$00,$00,$00,$00,$10,$0C,$0C,$0C,$48
defb $CC,$CC,$CC,$CC,$88,$00,$00,$00,$00,$00,$10,$0C,$0C,$0C,$18
defb $CC,$CC,$CC,$CC,$88,$00,$00,$00,$00,$00,$10,$0C,$0C,$0C,$18
defb $44,$CC,$CC,$CC,$20,$00,$00,$00,$00,$00,$04,$0C,$0C,$0C,$48
defb $44,$CC,$CC,$CC,$60,$00,$00,$00,$00,$00,$84,$18,$30,$30,$20
defb $00,$00,$44,$CC,$30,$00,$00,$00,$00,$00,$24,$48,$00,$00,$00
defb $00,$00,$44,$98,$24,$00,$00,$00,$00,$00,$0C,$20,$00,$00,$00
defb $00,$00,$CC,$C8,$24,$80,$00,$00,$00,$40,$0C,$20,$00,$00,$00
defb $00,$00,$CC,$C8,$0C,$20,$00,$00,$00,$10,$0C,$80,$00,$00,$00
defb $00,$00,$CC,$88,$24,$20,$00,$00,$00,$10,$0C,$00,$00,$00,$00
defb $00,$44,$CC,$00,$24,$08,$00,$00,$00,$04,$18,$00,$00,$00,$00
defb $00,$44,$CC,$00,$84,$48,$00,$00,$00,$84,$18,$00,$00,$00,$00
defb $00,$44,$CC,$00,$04,$18,$44,$CC,$CC,$CC,$CC,$CC,$CC,$00,$00
defb $00,$00,$88,$00,$10,$0C,$64,$CC,$CC,$CC,$CC,$CC,$CC,$00,$00
defb $00,$00,$88,$00,$10,$0C,$64,$CC,$CC,$CC,$CC,$CC,$CC,$00,$00
defb $00,$00,$88,$00,$10,$0C,$64,$CC,$CC,$CC,$CC,$CC,$CC,$00,$00
defb $00,$00,$88,$00,$10,$0C,$30,$CC,$CC,$CC,$CC,$CC,$CC,$00,$00
defb $00,$00,$00,$00,$10,$0C,$48,$CC,$CC,$CC,$CC,$CC,$88,$00,$00
defb $00,$00,$00,$00,$04,$0C,$48,$00,$00,$CC,$88,$00,$00,$00,$00
defb $00,$00,$00,$00,$84,$0C,$18,$00,$00,$44,$88,$00,$00,$00,$00
defb $00,$00,$00,$00,$24,$0C,$0C,$00,$00,$44,$CC,$00,$00,$00,$00
defb $00,$00,$00,$00,$0C,$18,$0C,$80,$00,$44,$CC,$00,$00,$00,$00
defb $00,$00,$00,$40,$0C,$60,$0C,$20,$00,$44,$CC,$00,$00,$00,$00
defb $00,$00,$00,$10,$0C,$80,$24,$20,$00,$00,$CC,$88,$00,$00,$00
defb $00,$00,$00,$10,$18,$00,$24,$48,$00,$00,$CC,$88,$00,$00,$00
defb $00,$00,$00,$10,$18,$00,$84,$18,$00,$00,$CC,$88,$00,$00,$00
defb $00,$00,$00,$10,$48,$00,$04,$18,$00,$00,$44,$88,$00,$00,$00
defb $00,$00,$00,$40,$48,$00,$10,$0C,$00,$00,$44,$00,$00,$00,$00
._tintas
defb 11,13,26,28,28,28,28,28,28,28,28,28,28,28,28,99
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
    const char height = 52;
    const char width  = 15;
    int scr = 0xC000;

    unsigned char *buffer[15*52];
    memcpy(buffer,nixos,height*width);

    mirrored(buffer,height,width,2);
    cpc_DisableFirmware();
    cpc_SetMode(0);

    cpc_PutSp(buffer,height,width,scr);
    cpc_PutSpXOR(nixos,height,width,scr+width);  // cpc_PutSp(char *sprite, int height, int width, unsigned int address)

    while (!cpc_AnyKeyPressed()){}   
}
