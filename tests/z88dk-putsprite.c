/*
    usefull documentation : https://www.z88dk.org/wiki/doku.php?id=library:sprites:monosprites
    zcc +cpc -v -lcpcfs -lm -create-app -subtype=dsk z88dk-putsprite.c -o z88dk-putsprite.dsk                                     
    cap32 -a 'run"Z88DK-PU.CPC' z88dk-putsprite.dsk
    -Wlimited-range ?
 */

#include <cpc.h>
#include <stdio.h>
#include <games.h>
#include "z88dk-putsprite.h"

struct Sprite {
    uchar height;
    uchar width;
    uchar buffer[];
};

//TODO : uchar -> uint
inverse_color(uchar * buffer, const uchar height , const uchar width )
{
    int i = 0;
    while ( i < width * height ) {
        buffer[i] = ~buffer[i];
        i++;
    }
}

main()
{
    
    cpc_SetBorder(3);
    cpc_DisableFirmware();
    cpc_SetMode(2);
    // https://codeforwin.org/2017/12/access-two-dimensional-array-using-pointers-c-programming.html
    // inverse_color(&(sprite+2),sprite[0],sprite[1]); 
    putsprite(SPR_OR, 0, 0, sprite);
    while (!cpc_AnyKeyPressed()){}   
}
