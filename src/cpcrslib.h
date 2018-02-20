#ifndef __CPCRSLIB_H__
#define __CPCRSLIB_H__

#include <stdbool.h>
#include <wand/MagickWand.h>
#include <string.h>
#include <libgen.h>
#include "cpcutils.h"

int cpcrslib(MagickWand *image_wand, char **outBuffer, bool masked, unsigned char mode);

#endif
