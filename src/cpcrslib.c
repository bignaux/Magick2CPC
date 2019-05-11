#include "cpcrslib.h"

/**
 * Convert an image to a cpcrslib sprite or tile
 * @param image_wand the magick wand to transform
 * @param outBuffer destination buffer after transformation
 * @param masked if true, generate masked sprite
 * @param mode CPC graphic mode @ref cpc_mode
 * @return size of outBuffer
 */

int cpcrslib(MagickWand *image_wand, char **outBuffer, bool masked, unsigned char mode)
{

	char *localPointer;
	long y;
	size_t columns, rows;
	PixelIterator *iterator;
	PixelWand **pixels;
	register long x;
	int bufcnt;
	int palettesize;

	int ppb = (int) modes[mode].ppb;
	unsigned char pixel;
	unsigned char databyte[ppb];
	unsigned char maskbyte[ppb];
	int j;

	unsigned char palette[modes[mode].nbcolors];
	memset(palette, 28, modes[mode].nbcolors * sizeof(unsigned char));
	palettesize = 16 + 2 * modes[mode].nbcolors * sizeof(unsigned char);

	char * filename = MagickGetImageFilename(image_wand);

	columns = MagickGetImageHeight(image_wand);
	rows = MagickGetImageWidth(image_wand);

	fprintf(stderr,"Size %ldx%ld\n", columns, rows);
	// Labels can be up to 14(?) characters in length
	int outSize = palettesize + columns * (5 + 4 * rows) * sizeof(char) + 100; // 100 to store buffer name and size...
	fprintf(stderr,"outSize=%d\n", outSize);
	localPointer = (char*) malloc(outSize);
	if (localPointer == NULL)
	{
		perror(":malloc");
		return 0;
	}

	/*
	 * convert it into a buffer
	 */
	filename = basename(filename);

	bufcnt = sprintf(localPointer, "._%s\ndefb %d,%d", filename,
			(int) rows / 2, (int) columns);
	iterator = NewPixelIterator(image_wand);
	if (iterator == (PixelIterator *) NULL)
		ThrowWandException(image_wand);
	for (y = 0; y < (long) columns; y++)
	{
		pixels = PixelGetNextIteratorRow(iterator, &rows);
		if (pixels == (PixelWand **) NULL)
			break;
		bufcnt += sprintf(localPointer + bufcnt, "\ndefb ");
		for (x = 0; x < (long) rows; x++)
		{
			// could it be replace by modulo
			for (j = 0; j < ppb; j++)
			{
				if (masked)
				{
					if (PixelGetAlpha(pixels[x + j]))
						maskbyte[j] = 0x00;
					else
						maskbyte[j] = 0xFF;
				}
				databyte[j] = palettise(pixel2cpc(pixels[x + j]), palette,
						modes[mode].nbcolors);
			}
			if (masked)
			{
				pixel = cpc2displaypixeldata(maskbyte, ppb);
				bufcnt += sprintf(localPointer + bufcnt, "$%2.2X,", pixel);
			}
			pixel = cpc2displaypixeldata(databyte, ppb);
			bufcnt += sprintf(localPointer + bufcnt, "$%2.2X,", pixel);
			// verify with ppb != 2
			x += ppb - 1;
		}
		bufcnt--;
	}
	bufcnt += sprintf(localPointer + bufcnt, "\n");

	if (y < (long) columns)
		ThrowWandException(image_wand);
	iterator = DestroyPixelIterator(iterator);
	image_wand = DestroyMagickWand(image_wand);
	MagickWandTerminus();

	// not tested yet
	qsort(palette, modes[mode].nbcolors, sizeof(char), sort);
	bufcnt += sprintf(localPointer + bufcnt, "\n._tintas\ndefb ");
	for (j = 0; j < 15; j++)
		bufcnt += sprintf(localPointer + bufcnt, "%d,", palette[j]);
	bufcnt += sprintf(localPointer + bufcnt, "%d\n", palette[++j]);

	*outBuffer = localPointer;
	return bufcnt;
}
