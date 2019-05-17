#include "z88.h"

/**
 *  generate sprite for the z88dk putsprite function ( 1bit per pixel )
 */

int z88(MagickWand * image_wand, char **outBuffer, bool comment)
{

	char *localPointer;
	long y;
	size_t columns, rows;
	PixelIterator *iterator;
	PixelWand **pixels;
	register long x;
	int bufcnt = 0;
	int commentcnt = 0;
	unsigned char total = 0;
	int bits = 0;
	int outSize = 0;

	columns = MagickGetImageHeight(image_wand);
	rows = MagickGetImageWidth(image_wand);

	fprintf(stderr,"Size %ldx%ld\n", columns, rows);

	/* comment buffer */
	if (comment)
	{
		outSize = rows * (columns + 1) * sizeof(char) + 6;
		bufcnt = outSize;
	}

	/* data buffer */

	/// @todo better calculation of size
	outSize += rows * columns * sizeof(char) + 100;// 100 to store buffer name and size...
	fprintf(stderr,"outSize=%d\n", outSize);
	localPointer = (char*) malloc(outSize);
	if (localPointer == NULL)
	{
		perror("malloc()");
		return 0;
	}
	/// @todo manage spritename
	bufcnt += sprintf(localPointer + bufcnt, "char sprite[] = {\n %d, %d, \n",
			(int) rows, (int) columns);

	if (comment)
		commentcnt = sprintf(localPointer + commentcnt, "/*\n");

	/*
	 convert it into a buffer
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
			if (PixelGetBlack(pixels[x]))
			{
				total |= (1 << (7 - bits));
				if (comment)
					commentcnt += sprintf(localPointer + commentcnt, "%c",
							PIXEL);
			}
			else if (comment)
				commentcnt += sprintf(localPointer + commentcnt, "%c", NOPIXEL);
			if ((bits == 7) || (x == rows - 1))
			{
				bufcnt += sprintf(localPointer + bufcnt, " 0x%2.2X,", total);
				total = 0;
				bits = 0;
			}
			else
				bits++;
		}
		bufcnt += sprintf(localPointer + bufcnt, "\n");
		if (comment)
			commentcnt += sprintf(localPointer + commentcnt, "\n");
	}

	bufcnt += sprintf(localPointer + bufcnt - 2, " };\n");
	bufcnt--;

	if (comment)
		commentcnt += sprintf(localPointer + commentcnt, "*/\n");

	if (y < (long) columns)
		ThrowWandException(image_wand);
	iterator = DestroyPixelIterator(iterator);
	image_wand = DestroyMagickWand(image_wand);
	MagickWandTerminus();

	*outBuffer = localPointer;
	return bufcnt;
}
