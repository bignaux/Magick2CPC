#ifndef __RASTER_H__
#define __RASTER_H__

#include <wand/MagickWand.h>
#include <string.h>
#include "cpcutils.h"

int raster(MagickWand *image_wand, char **outBuffer);

#endif
