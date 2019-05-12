/*
 *  usefull documentation : http://www.mojontwins.com/warehouse/splib2-tutorial.pdf
 *  zcc +cpc -v -lcpcfs -lm -create-app -subtype=dsk z88dk-cpc_PutSp.c -o z88dk-cpc_PutSp.dsk
 *  cap32 -a 'run"z88dk-cp.cpc' z88dk-cpc_PutSp.dsk
 */

#include <cpc.h>
#include <stdio.h>
#include "z88dk-cpc_PutSp.h"

extern uchar tintas[];
extern uchar nixos[];

struct Sprite {
    uchar height;
    uchar width;
    uchar buffer[];
};

uchar
swapNibbles(uchar x)
{
    return ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 );
}

uchar
swapBitsInPair(uchar x)
{
    // Extracting the high bit shift it to lowbit
    // Extracting the low bit shift it to highbit
    return ((x & 0b10101010) >> 1)
           | ((x & 0b01010101) << 1);
}

/* ppb : pixels per byte */
mirrored(uchar * buffer, const uchar height, const uchar width, const uchar ppb)
{
    uchar temp, * pbuffer = buffer;
    uchar w, h = 0;
    void * swap_ptr; // Z88DK does not allow function pointers to be prototyped

    if (ppb == 2) swap_ptr = &swapBitsInPair;
    else if (ppb == 4) swap_ptr = &swapNibbles;  // TODO
    else if (ppb == 8) swap_ptr = &swapNibbles;  // TODO http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious

    while (h < height) {
        while (w < width / 2) {
            temp = swap_ptr(*(pbuffer + w));
            *(pbuffer + w) = swap_ptr(*(pbuffer + width - w - 1));
            *(pbuffer + width - w - 1) = temp;
            w++;
        }
        pbuffer += width;
        w        = 0;
        h++;
    }
}

// see http://www.mojontwins.com/mojoniaplus/viewtopic.php?t=1820#p61485
// BUGS: last color of palette is > 26
const uchar firm2hard[] = { 20, 4,  21, 28, 24, 29, 12, 5,  
                            13, 22, 6,  23, 30, 0, 31, 14,
                            7, 15, 18, 2,  19, 26, 25, 27, 10, 3,  11 };

void
set_palette(const uchar * ink, const uchar ppb)
{
    uchar i, j;

    if (ppb == 2) i = 16;   
    else if (ppb == 4) i = 4;
    else if (ppb == 8) i = 2;

    for (j = 0; j < i; j++) {
        cpc_SetColour(j, firm2hard[ink[j]]);
    }
}

main()
{
    uint scr = 0xC000;
    uint i   = 0;
    uchar * pbuffer;

    unsigned char * buffer[15 * 52];

    memcpy(buffer, nixos, 52 * 15);

    // int size = sizeof(nixos);
    // unsigned char txt_numb[4];
    // itoa(size,txt_numb,10);
    // cpc_PrintGphStrXY(txt_numb,0,0);

    mirrored(buffer, 52, 15, 2);

    set_palette(tintas, 2);

    cpc_SetBorder(10);
    cpc_DisableFirmware();
    cpc_SetMode(0);

    // pbuffer = buffer; // z88dk doesn't accept buffer += 4; ?!
    // for (i=0; i < 0xFFFF; i++) {
    //     cpc_PutSp( buffer, 1, 15, scr );
    //     // pbuffer =  4;
    //     scr += 0x800;
    //     if (!(scr & 0x3800))
    //       scr += 0xC050;
    // }
    // cpc_PutSp(buffer,52,15,scr);

    // TODO : input png dimension has to be multiple of 2
    cpc_PutSpXOR(nixos, 200, 78, scr); // cpc_PutSp(char *sprite, int height, int width, unsigned int address)

    while (!cpc_AnyKeyPressed()) { }
}
