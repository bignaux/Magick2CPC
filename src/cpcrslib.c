#include "cpcrslib.h"

struct image {
	unsigned char *pixelarray;
	size_t columns;
	size_t rows;
	unsigned char *palette;
	char *filename;
	char ppb;
};

/**
 * Convert an image to a cpcrslib sprite or tile
 * @param image_wand the magick wand to transform
 * @param outBuffer destination buffer after transformation
 * @param masked if true, generate masked sprite
 * @param mode CPC graphic mode @ref cpc_mode
 * @return size of outBuffer
 */

int convert(MagickWand *image_wand, struct image *img, bool masked)
{
	long y;
	size_t 	nbcolors = MagickGetImageColors(image_wand);
	img->ppb = nbcolors / 8 ; //TODO
	PixelIterator *iterator;
	PixelWand **pixels;
	register long x;

	unsigned char databyte[img->ppb];
	unsigned char maskbyte[img->ppb];
	int j;

	img->palette = malloc(nbcolors); // TODO : remove from here
	memset(img->palette, 28, nbcolors * sizeof(unsigned char));

	img->columns = MagickGetImageHeight(image_wand);
	img->rows = MagickGetImageWidth(image_wand);
	img->pixelarray = (unsigned char *) malloc (img->rows * img->columns / img->ppb);
	unsigned char *ptrpixelarray = img->pixelarray;


	char * filename = MagickGetImageFilename(image_wand);
	img->filename = malloc(strlen(filename) + 1);
	img->filename = strcpy(img->filename,filename);

	fprintf(stderr,"Size %ldx%ld , %ld colors, %d depth.\n", 
		img->columns, img->rows, nbcolors, img->ppb);


	/*
	 * convert it into a char array
	 */

	iterator = NewPixelIterator(image_wand);
	if (iterator == (PixelIterator *) NULL)
		ThrowWandException(image_wand);
	for (y = 0; y < (long) img->columns; y++)
	{
		pixels = PixelGetNextIteratorRow(iterator, &img->rows);
		if (pixels == (PixelWand **) NULL)
			break;
		for (x = 0; x < (long) img->rows; x++)
		{
			// could it be replace by modulo
			for (j = 0; j < img->ppb; j++)
			{
				if (masked)
				{
					if (PixelGetAlpha(pixels[x + j]))
						maskbyte[j] = 0x00;
					else
						maskbyte[j] = 0xFF;
				}
				databyte[j] = palettise(pixel2cpc(pixels[x + j]), img->palette,
						nbcolors);
			}
			if (masked)
			{
				*(ptrpixelarray++) = cpc2displaypixeldata(maskbyte, img->ppb);
			}
			*(ptrpixelarray++) = cpc2displaypixeldata(databyte, img->ppb);
			x += img->ppb - 1; // TODO : mode 0
		}
	}

	if (y < (long) img->columns)
		ThrowWandException(image_wand);
	iterator = DestroyPixelIterator(iterator);
	image_wand = DestroyMagickWand(image_wand);
	MagickWandTerminus();

	return (EXIT_SUCCESS);
}

int cpcrslib(MagickWand *image_wand, char **outBuffer, bool masked)
{
	int bufcnt = 0;
	char *localPointer = malloc(100);
	struct image img;

	convert(image_wand, &img, masked);

	bufcnt += sprintf(localPointer + bufcnt, "/*\t\tGenerated by Magick2CPC : DO NOT EDIT.\t\t*/\n");
	bufcnt += sprintf(localPointer + bufcnt, "\n#asm\n");
	bufcnt += FormatAsmArray(&localPointer, img.pixelarray, 
		img.rows / img.ppb , img.columns , img.filename, "$%2.2X");
	bufcnt += FormatAsmArray(&localPointer, img.palette, 1, 16, "tintas", "%d" ); //TODO nbcolors
	bufcnt += sprintf(localPointer + bufcnt, "#endasm\n");

	*outBuffer = localPointer;
	fprintf(stderr, "localPointer = 0x%p\n", localPointer);
	return bufcnt;
}

