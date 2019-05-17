#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <wand/MagickWand.h>
#include "cpc.h"

int FormatAsmArray(char ** outBuffer, const unsigned char * array, 
	const int rows, const int columns, const char * name, const char * format);

#endif
