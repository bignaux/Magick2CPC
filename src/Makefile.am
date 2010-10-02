## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(MAGICK2CPC_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = magick2cpc

magick2cpc_SOURCES = \
	main.c      \
	cpcutils.c      \
	cpcutils.h      \
	cpc.h      \
	z88.c      \
	z88.h      \
	raster.c      \
	raster.h      \
	cpcrslib.c      \
	cpcrslib.h

magick2cpc_LDFLAGS = 

magick2cpc_LDADD = $(MAGICK2CPC_LIBS)

