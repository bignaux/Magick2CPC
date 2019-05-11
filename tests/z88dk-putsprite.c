/*
    usefull documentation : https://www.z88dk.org/wiki/doku.php?id=library:sprites:monosprites

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
    cpc_DisableFirmware();
    cpc_SetMode(2);
    // inverse_color(*(sprite+2),sprite[0],sprite[1]);
    putsprite(SPR_OR, 0, 0, sprite);
    while (!cpc_AnyKeyPressed()){}   
}
