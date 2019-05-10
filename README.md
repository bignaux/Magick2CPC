Magick2CPC
==========
[![Build Status](https://travis-ci.org/bignaux/Magick2CPC.svg?branch=master)](https://travis-ci.org/bignaux/Magick2CPC/)

An image converter for CPC using ImageMagick.
/!\ THIS SOFTWARE IS UNDER DEVELOPEMENT
Feel free to join the project @ http://github.com/bignaux/Magick2CPC/

- What is Magick2CPC?
- Current features, usage and status
- Limitations and issues
- Licensing
- Installation of Magick2CPC
- TODO

What is Magick2CPC?
------------------

Magick2CPC is an image converter that produce source code to CPC and other target. It supports
all ImageMagick image format but doest rezise image for you. You have to provide well sized image
that fit with the feature you want to perform. Unlike graphic tools, it tend to be integrating 
as a part of a toolchain like in Makefile.

Magick2CPC :

- is scriptable
- is easy hackable
- is portable 
- is opensource and developer welcome ( git, wiki and bugtracker @ github ) 
- uses the powerful MagickWand to have many image processing features

Current features and usage:
--------------------------------

**z88dk sprite**

Magick2cpc can produce source code for putsprite().
http://www.z88dk.org/wiki/doku.php?id=library:sprites:monosprites
if --boolean option is used, it add a visualisation of the image as a comment.
STATUS : OK

**cpcrslib sprite**

https://sourceforge.net/projects/cpcrslib/
if --boolean option is used, it produces non masked sprite.

STATUS : NEED SOME WORK

http://www.amstrad.es/espsoft/herramientas/sprot11.html graphic tool, Windows, closed source

**CPC assembly raster** 
STATUS : OK

Limitations and issues:
----------------------

This concerns current situation,  therefore do not understand those as
immutable issues!

- tested only on Linux (other OS support is planned)
- you should provide ready to transform image.
- No CPC+ specific

Licensing:
---------

Magick2CPC is licensed under the GPLv3. A copy of this license is provided
with Magick2CPC archive.

Installation of Magick2CPC:
----------------------

A configure  script is provided. If  you get some trouble  with it you
will be able to recreate it while running autogen.sh script.

Run: 
	 ./configure

Note that having libmagickwand-dev installed is MANDATORY.

Then run:

	 make && make install

A more detailed documentation about installation is provided in Magick2CPC
archive  in INSTALL  document. If  you want  to change  de  prefix for
instance.

TODO :
----

[general]
- manage sprite name
- write examples

[cpcrslib.c] :
- manage if image is not multiple of ppb
- better alpha layer management
- palette management : in progress [cpcutils.c]

* Use ImageMagick "Custom Image Coders" to provide ImageMagick plugins, see :
- http://www.imagemagick.org/script/architecture.php
- http://trac.imagemagick.org/browser/ImageMagick/trunk/coders/
- http://www.sportmarketing-tbb.de/doc/libmagick4-dev/blob.html

* Work with multiple image wand, see :
- MagickHasPreviousImage() returns MagickTrue if the wand has more images when traversing the list in the reverse direction
- MagickDeconstructImages() compares each image with the next in a sequence and returns the maximum bounding region of any pixel differences it discovers.

