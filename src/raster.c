#include "raster.h"

/*
 * generate raster in assembly
 */

int raster(MagickWand *image_wand, char **outBuffer)
{

	char *localPointer;
	PixelIterator *iterator;
	PixelWand **pixels;
	register long x;
	long y;
	unsigned long columns, rows;
	int bufcpt = 0;
	int cpt = 0;

	/*
	 * allocate buffer
	 */

	columns = MagickGetImageHeight(image_wand);
	rows = MagickGetImageWidth(image_wand);

	printf("Image size : %ldx%ld\n", columns, rows);
	int outSize = 9 * rows * columns * sizeof(char) ;
	localPointer = (char*) malloc(outSize);
	if (localPointer == NULL)
	{
		perror("malloc");
		return 0;
	}

	/*
	 * convert wand into a buffer
	 */

	iterator = NewPixelIterator(image_wand);
	if (iterator == (PixelIterator *) NULL)
		ThrowWandException(image_wand);
	for (y = 0; y < (long) columns; y++)
	{
		pixels = PixelGetNextIteratorRow(iterator, &rows);
		if (pixels == (PixelWand **) NULL)
			break;
		for (x = 0; x < (long) rows; x++)
		{
			cpt = sprintf(localPointer + bufcpt, "defb &%2.2X\n", cpc2raster(pixel2cpc(pixels[x])));
			bufcpt += cpt;
		}
	}

	if (y < (long) columns)
		ThrowWandException(image_wand);
	iterator = DestroyPixelIterator(iterator);
	image_wand = DestroyMagickWand(image_wand);
	MagickWandTerminus();

	*outBuffer = localPointer;
	return bufcpt;
}
