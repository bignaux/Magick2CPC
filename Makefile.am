## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

magick2cpcdocdir = ${prefix}/doc/magick2cpc
magick2cpcdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(magick2cpcdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(magick2cpcdocdir)
