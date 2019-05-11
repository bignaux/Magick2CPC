#include "cpcutils.h"

int sort(const void *x, const void *y) {
  return (*(char*)x - *(char*)y);
}

/**
 convert RGB pixel from the wand to 3-level RGB
 @return the software color read in cpc_color_soft[] table.
 */
unsigned char pixel2cpc(const PixelWand *wand)
{
	//sfprintf(stderr,pixelstring,"$FF,$xx"); //,PixelGetAlpha(wand),PixelGetRed(wand));
	double rgb[3] =
	{ PixelGetRed(wand), PixelGetGreen(wand), PixelGetBlue(wand) };
	//fprintf(stderr,"r=%f,g=%f,b=%f",rgb[0],rgb[1],rgb[2]);
	unsigned char cpc_rgb[3] =
	{ 0, 0, 0 };
	int i;
	for (i = 0; i < 3; i++)
	{
		if (rgb[i] >= 0.66)
			cpc_rgb[i] = 0xFF;
		else if ((rgb[i] > 0.33) && (rgb[i] < 0.66))
			cpc_rgb[i] = 0x7F;
	}
	//fprintf(stderr,"r=%x,g=%x,b=%x",cpc_rgb[0],cpc_rgb[1],cpc_rgb[2]);
	for (i = 0; i < 27; i++)
	{
		if ((cpc_rgb[0] == cpc_color_soft[i][0]) && (cpc_rgb[1]
				== cpc_color_soft[i][1])
				&& (cpc_rgb[2] == cpc_color_soft[i][2]))
		{
			return (char) i;
			//i=27;
		}
	}
	return -1;
}

/**
 * Return the hardware color from a software one according to @ref soft_to_hw table.
 * @param the software color
 * @return the hardware color
 */
unsigned char cpc2raster(unsigned char soft_colornum)
{
	// bit 7=0, bit 6=1 = Gate Array function "write colour"
	// bit 4..0 = hardware colour number
	return (soft_to_hw[soft_colornum]);
}

/**
 *	@return pixel indexed color of cpcpixel and complete palette
 *	@todo manage image with less than nbcolors
 */
unsigned char palettise(unsigned char cpcpixel,unsigned char * palette, char nbcolors)
{
	int i;
	//  we could try to memorize last color and test it first .
	for (i = 0; i < nbcolors; i++)
	{
		if (palette[i] == 28)
			palette[i] = cpcpixel;
		if (cpcpixel == palette[i])
			return (unsigned char) i;
	}
	fprintf(stderr,"palettise error\n");
	return 0;
}

unsigned char cpc2displaypixeldata2ppb(unsigned char * pixel)
{
	unsigned char byte_tmp0 = *pixel;
	unsigned char byte_tmp1 = *(pixel + 1);
	unsigned char byte_tmp = (((byte_tmp1 & 0x08) >> 3) | ((byte_tmp1 & 0x04)
			<< 2) | ((byte_tmp1 & 0x02) << 1) | ((byte_tmp1 & 0x01) << 6)
			| ((byte_tmp0 & 0x08) >> 2) | ((byte_tmp0 & 0x04) << 3)
			| ((byte_tmp0 & 0x02) << 2) | ((byte_tmp0 & 0x01) << 7));
	return byte_tmp;
}

/*untested */
unsigned char cpc2displaypixeldata4ppb(unsigned char * pixel)
{
	unsigned char byte_tmp0 = *pixel;
	unsigned char byte_tmp1 = *(pixel + 1);
	unsigned char byte_tmp2 = *(pixel + 2);
	unsigned char byte_tmp3 = *(pixel + 3);
	unsigned char byte_tmp = (((byte_tmp3 & 0x02) >> 1) | ((byte_tmp3 & 0x01)
			<< 4) | ((byte_tmp2 & 0x02)) | ((byte_tmp2 & 0x01) << 5)
			| ((byte_tmp1 & 0x02) << 1) | ((byte_tmp1 & 0x01) << 6)
			| ((byte_tmp0 & 0x02) << 2) | ((byte_tmp0 & 0x01) << 7));
	return byte_tmp;
}

/*untested */
unsigned char cpc2displaypixeldata8ppb(unsigned char * pixel)
{
	unsigned char byte_tmp0 = *pixel;
	unsigned char byte_tmp1 = *(pixel + 1);
	unsigned char byte_tmp2 = *(pixel + 2);
	unsigned char byte_tmp3 = *(pixel + 3);
	unsigned char byte_tmp4 = *(pixel + 4);
	unsigned char byte_tmp5 = *(pixel + 5);
	unsigned char byte_tmp6 = *(pixel + 6);
	unsigned char byte_tmp7 = *(pixel + 7);
	unsigned char byte_tmp = (((byte_tmp7 & 0x01)) | ((byte_tmp6 & 0x01) << 1)
			| ((byte_tmp5 & 0x01) << 2) | ((byte_tmp4 & 0x01) << 3)
			| ((byte_tmp3 & 0x01) << 4) | ((byte_tmp2 & 0x01) << 5)
			| ((byte_tmp1 & 0x01) << 6) | ((byte_tmp0 & 0x01) << 7));
	return byte_tmp;
}

unsigned char cpc2displaypixeldata(unsigned char * pixel, int ppb)
{
	if (ppb == 2)
		return cpc2displaypixeldata2ppb(pixel);
	else if (ppb == 4)
		return cpc2displaypixeldata4ppb(pixel);
	else if (ppb == 8)
		return cpc2displaypixeldata8ppb(pixel);
	else
		return 0;
}
