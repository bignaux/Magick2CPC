/*
    usefull documentation : http://www.mojontwins.com/warehouse/splib2-tutorial.pdf
 */

#include <cpc.h>
#include <stdio.h>
#include "nixos.h"

struct Sprite {
    uchar height;
    uchar width;
    uchar buffer[];
};

uchar swapNibbles(uchar x) 
{ 
    return ( (x & 0x0F)<<4 | (x & 0xF0)>>4 ); 
} 

uchar swapBitsInPair(uchar x) 
{ 
    // Extracting the high bit shift it to lowbit 
    // Extracting the low bit shift it to highbit 
    return ((x & 0b10101010) >> 1) |  
            ((x & 0b01010101) << 1);     
} 

mirrored(uchar * buffer, const uchar height, const uchar width, const uchar ppb )
{
    uchar temp, *pbuffer = buffer;
    uchar w,h = 0;
    void *swap_ptr; // Z88DK does not allow function pointers to be prototyped

    if ( ppb == 2 ) swap_ptr = &swapBitsInPair;
    else if ( ppb == 4 ) swap_ptr = &swapNibbles; // TODO
    else if ( ppb == 8 ) swap_ptr = &swapNibbles; // TODO http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious

    while ( h < height ) {
        while ( w < width / 2 ) {
            temp = swap_ptr(*(pbuffer+w));
            *(pbuffer+w) = swap_ptr(*(pbuffer+width - w -1));
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
    uint scr = 0xC000;

    unsigned char *buffer[15*52];
    memcpy(buffer,nixos,52*15);

    // int size = sizeof(nixos);
    // unsigned char txt_numb[4];
    // itoa(size,txt_numb,10);
    // cpc_PrintGphStrXY(txt_numb,0,0);

    mirrored(buffer,52,15,2);
    cpc_DisableFirmware();
    cpc_SetMode(0);

    cpc_PutSp(buffer,52,15,scr);
    cpc_PutSpXOR(nixos,52,15,scr+15);  // cpc_PutSp(char *sprite, int height, int width, unsigned int address)

    while (!cpc_AnyKeyPressed()){}   
}
