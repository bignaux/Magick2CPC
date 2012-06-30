/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Bignaux Ronan 2010 <ronan@aimao.org>
 *
 * magick2cpc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * magick2cpc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "z88.h"
#include "raster.h"
#include "cpcrslib.h"
#include <wand/MagickWand.h>

#define CONFIG_PARAMS "r:c:z:o:bh"

#define MAGICK2CPC_USAGE "Usage: magick2cpc [-crzobh]\n\
--cpcrslib,-c image\n\
--raster,-r image\n\
--z88,-z image\n\
--output,-o output\n\
--boolean,-b boolean_option\n\
--help,-h shows this help message\n"

const struct option magick2cpc_config_opts[] =
{
{ "raster", required_argument, NULL, 'r' },
{ "cpcrslib", required_argument, NULL, 'c' },
{ "z88", required_argument, NULL, 'z' },
{ "output", required_argument, NULL, 'o' },
{ "boolean", no_argument, NULL, 'b' },
{ "help", no_argument, NULL, 'h' },
{ NULL, no_argument, NULL, 0 } };

void writebuffer(char * filename, int bufferSize, char *outBuffer)
{
	FILE *outFile;
	size_t written;
	outFile = fopen(filename, "wb");
	if (outFile == NULL)
	{
		perror("__func__  fopen");
		exit(EXIT_FAILURE);
	}
	printf("Write %d bytes in %s\n", bufferSize, filename);
	written = fwrite(outBuffer, 1, bufferSize, outFile);
	if ( written != bufferSize )
	{
		perror("__func__ :fwrite");
		// ret = EXIT_FAILURE;
	}
	fclose(outFile);
	free(outBuffer);
	outBuffer = NULL;
}

MagickWand * openimage(char * filename)
{
	MagickWand *image_wand;
	MagickBooleanType status;
	MagickWandGenesis(); // initializes the MagickWand environment.
	image_wand = NewMagickWand();
	status = MagickReadImage(image_wand, filename);
	if (status == MagickFalse)
		ThrowWandException(image_wand); // exit with failure
	return image_wand;
}

int main(int argc, char **argv)
{
	MagickWand *image_wand;
	char *filename = NULL;
	char *outBuffer;
	int bufferSize = 0;
	bool optbool = false;

	const char *all_params = CONFIG_PARAMS;
	int long_index;
	int option;
	char mode = 0;
	int m_idx = 0;

	do
	{
		option = getopt_long(argc, argv, all_params, magick2cpc_config_opts,
				&long_index);

		switch (option)
		{
		case 'r':
			image_wand = openimage(optarg);
			bufferSize = raster(image_wand, &outBuffer);
			break;
		case 'c':
			image_wand = openimage(optarg);
			bufferSize = cpcrslib(image_wand, &outBuffer, optbool, mode);
			break;
		case 'z':
			image_wand = openimage(optarg);
			bufferSize = z88(image_wand, &outBuffer, optbool);
			break;
		case 'o':
			filename = optarg;
			break;
		case 'b':
			optbool = true;
			break;
		case 'h':
			fprintf(stdout, MAGICK2CPC_USAGE);
			exit(EXIT_SUCCESS);
			break;
		case '?':
			fprintf(stdout, "Use --help, -h option for more informations.\n");
			exit(EXIT_FAILURE);
			break;
		default:
			break;
		}
		m_idx++;

		if (bufferSize > 0 && filename != NULL)
		{
			writebuffer(filename, bufferSize, outBuffer);
			filename = NULL;
			bufferSize = 0;
		}

	} while (option != -1);

	return (EXIT_SUCCESS);
}
