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

main()
{
    cpc_DisableFirmware();
    cpc_SetMode(2);
    putsprite(SPR_OR, 0, 0, sprite);
    while (!cpc_AnyKeyPressed()){}   
}
