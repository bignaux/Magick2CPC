#ifndef __CPCUTILS_H__
#define __CPCUTILS_H__

#include <wand/MagickWand.h>
#include "cpc.h"

int sort(const void *x, const void *y);
unsigned char pixel2cpc(const PixelWand *wand);
unsigned char cpc2raster(unsigned char soft_colornum);
unsigned char palettise( const unsigned char cpcpixel,unsigned char * palette, const char nbcolors);
unsigned char cpc2displaypixeldata(unsigned char * pixel, int ppb);
unsigned char cpc2displaypixeldata2ppb(unsigned char * pixel);
unsigned char cpc2displaypixeldata4ppb(unsigned char * pixel);
unsigned char cpc2displaypixeldata8ppb(unsigned char * pixel);

#define ThrowWandException(wand) \
		{ \
			char \
			*description; \
	ExceptionType \
		severity; \
	description=MagickGetException(wand,&severity); \
	(void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
	description=(char *) MagickRelinquishMemory(description); \
	exit(-1); \
}

#endif
