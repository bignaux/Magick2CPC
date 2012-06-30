#ifndef __CPC_H__
#define __CPC_H__

/*
 * More information here :
 * http://www.cpcwiki.eu/index.php/Gate_Array#Palette_sorted_by_Hardware_Color_Numbers
 * http://cepece.info/amstrad/docs/graphics.html
 * http://www.cpcwiki.eu/index.php/Video_modes
 * http://www.grimware.org/doku.php/documentations/devices/crtc
 */

/**
 * @page cpc_mode CPC graphic modes :
 * @verbatim	
 * 		+-------+-------+-------+--------+---------+----------+
 * 		|  mode |  ppb 	|  bpp 	| colors |  normal | overscan |
 * 		+-------+-------+-------+--------+---------+----------+
 *		|	0	|	2	|   4	|   16   | 160x200 |  192x264 |
 * 		+-------+-------+-------+--------+---------+----------+
 *		|	1	|	4	|   2	| 	 4	 | 320x200 |  384x272 |
 * 		+-------+-------+-------+--------+---------+----------+
 * 		|	2	|	8	|   1	| 	 2	 | 640x200 |  768x272 |
 * 		+-------+-------+-------+--------+---------+----------+
 * 		|	3	|	?	|   2	| 	 4	 | 160x200 |	  N.C |
 * 		+-------+-------+-------+--------+---------+----------+
 * @endverbatim
 */

typedef struct
{
	int weight;
	int height;
} resolution;

typedef struct
{
	unsigned char ppb;
	unsigned char bpp;
	unsigned char nbcolors;
	resolution normal;
	resolution overscan;
} mode_info;

extern mode_info modes[4];
extern unsigned char cpc_color_soft[27][3];
extern unsigned char soft_to_hw[];

#endif
