with import (fetchTarball channel:nixos-19.03) {};

stdenv.mkDerivation {
  name = "magick2cpc";

  buildInputs =
    [ 
      imagemagick
      pkgconfig
      autoreconfHook
    ];
}
