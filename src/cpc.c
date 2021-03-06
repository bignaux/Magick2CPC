#include "cpc.h"

mode_info modes[4] = {
// ppb 	|  bpp 	| colors |  normal | overscan
{ 2 , 4 , 16, { 160 , 200 } , { 192 , 264 }},
{ 4 , 2 , 4 , { 320 , 200 } , { 384 , 272 }},
{ 8 , 1 , 2 , { 640 , 200 } , { 768 , 272 }},
{ 4 , 2 , 4 , { 160 , 200 } , { 0 , 0 }}};

unsigned char cpc_color_soft[27][3] =
{
{ 0x00, 0x00, 0x00 }, // Negro 			0
		{ 0x00, 0x00, 0x7F }, // Azul 			1
		{ 0x00, 0x00, 0xFF }, // Azul Brillante	2
		{ 0x7F, 0x00, 0x00 }, // Rojo				3
		{ 0x7F, 0x00, 0x7F }, // Magenta			4
		{ 0x7F, 0x00, 0xFF }, // Malva			5
		{ 0xFF, 0x00, 0x00 }, // Rojo Brillante	6
		{ 0xFF, 0x00, 0x7F }, // Purpura			7
		{ 0xFF, 0x00, 0xFF }, // Magenta Brillante8
		{ 0x00, 0x7F, 0x00 }, // Verde 			9
		{ 0x00, 0x7F, 0x7F }, // Cian				10
		{ 0x00, 0x7F, 0xFF }, // Azul Cielo		11
		{ 0x7F, 0x7F, 0x00 }, // Amarillo			12
		{ 0x7F, 0x7F, 0x7F }, // Blanco			13
		{ 0x7F, 0x7F, 0xFF }, // Azul Pastel		14
		{ 0xFF, 0x7F, 0x00 }, // Naranja			15
		{ 0xFF, 0x7F, 0x7F }, // Rosa				16
		{ 0xFF, 0x7F, 0xFF }, // Magenta Pastel	17
		{ 0x00, 0xFF, 0x00 }, // Verde Brillante	18
		{ 0x00, 0xFF, 0x7F }, // Verde Mar		19
		{ 0x00, 0xFF, 0xFF }, // Cian Brillante	20
		{ 0x7F, 0xFF, 0x00 }, // Lima				21
		{ 0x7F, 0xFF, 0x7F }, // Verde Pastel		22
		{ 0x7F, 0xFF, 0xFF }, // Cian Pastel		23
		{ 0xFF, 0xFF, 0x00 }, // Amarillo Brillante24
		{ 0xFF, 0xFF, 0x7F }, // Amarillo Pastel	25
		{ 0xFF, 0xFF, 0xFF } // Blanco Brillante	26
};

unsigned char soft_to_hw[] =
{ 0x54, 0x44, 0x55, 0x5c, 0x58, 0x5d, 0x4c, 0x45, 0x4d, 0x56, 0x46, 0x57, 0x5e,
		0x40, 0x5f, 0x4E, 0x47, 0x4F, 0x52, 0x42, 0x53, 0x5a, 0x59, 0x5b, 0x4a,
		0x43, 0x4b };
