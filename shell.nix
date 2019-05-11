#with import (fetchTarball channel:nixos-19.03) {};
with import <nixpkgs> {}; # nix-shell -I nixpkgs=/home/genesis/devel/nixpkgs

stdenv.mkDerivation rec{
  name = "magick2cpc";

  nativeBuildInputs = [  pkgconfig doxygen ];

  buildInputs =
    [ 
      imagemagick
      autoreconfHook
      ronn
    ] ++ checkInputs;

  checkInputs = [
      uncrustify
  	  caprice32
  	  z88dk
  	  gdb
  	  gdbgui # r -c nixos-logo-b\&w.png -o nixos.h
  	];
}
