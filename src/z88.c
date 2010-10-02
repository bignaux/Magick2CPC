#include "z88.h"

/*
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
	int bufcpt = 0;
	int cpt = 0;
	unsigned char total = 0;
	int bits = 0;
	int outSize = 0;

	int commentcpt = 0;

	columns = MagickGetImageHeight(image_wand);
	rows = MagickGetImageWidth(image_wand);

	printf("Size %ldx%ld\n", columns, rows);

	/* comment buffer */
	if (comment)
	{
		outSize = rows * (columns + 1) * sizeof(char) + 6;
		bufcpt = outSize;
	}

	/* data buffer */

	// TODO : better calculation of size
	outSize += rows * columns * sizeof(char) + 100;// 100 to store buffer name and size...
	printf("outSize=%d\n", outSize);
	localPointer = (char*) malloc(outSize);
	if (localPointer == NULL)
	{
		perror("malloc()");
		return 0;
	}
	//  TODO : manage spritename
	cpt = sprintf(localPointer + bufcpt, "char sprite[] = { %d, %d,",
			(int) rows, (int) columns);
	bufcpt += cpt;

	if (comment)
	{
		cpt = sprintf(localPointer + commentcpt, "/*\n");
		commentcpt += cpt;
	}

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
				{
					cpt = sprintf(localPointer + commentcpt, "%c", PIXEL);
					commentcpt += cpt;
				}
			}
			else
			{
				if (comment)
				{
					cpt = sprintf(localPointer + commentcpt, "%c", NOPIXEL);
					commentcpt += cpt;
				}
			}
			if ((bits == 7) || (x == rows - 1))
			{
				cpt = sprintf(localPointer + bufcpt, " 0x%2.2X,", total);
				bufcpt += cpt;
				total = 0;
				bits = 0;
			}
			else
				bits++;
		}
		if (comment)
		{
			cpt = sprintf(localPointer + commentcpt, "\n");
			commentcpt += cpt;
		}
	}

	cpt = sprintf(localPointer + bufcpt - 1, " };\n");
	bufcpt += cpt - 1;

	if (comment)
	{
		cpt = sprintf(localPointer + commentcpt, "*/\n");
		commentcpt += cpt;
	}

	if (y < (long) columns)
		ThrowWandException(image_wand);
	iterator = DestroyPixelIterator(iterator);
	image_wand = DestroyMagickWand(image_wand);
	MagickWandTerminus();

	*outBuffer = localPointer;
	return bufcpt;
}
