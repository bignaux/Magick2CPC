SUBDIRS = src 

magick2cpcdocdir = ${prefix}/doc/magick2cpc
magick2cpcdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(magick2cpcdoc_DATA)

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(magick2cpcdocdir)
