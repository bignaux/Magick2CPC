#ifndef __Z88_H__
#define __Z88_H__

#include <wand/MagickWand.h>
#include <string.h>
#include <stdbool.h>
#include "cpcutils.h"

#define PIXEL '#'
#define NOPIXEL '.'

int z88(MagickWand * image_wand, char **outBuffer, bool comment);

#endif
