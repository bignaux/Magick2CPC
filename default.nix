{ stdenv, fetchFromGitHub, imagemagick, pkgconfig, autoreconfHook }:

stdenv.mkDerivation rec {
  name = "magick2cpc-${version}";
  version = "2018-02-10";

  src = fetchFromGitHub {
    owner = "bignaux";
    repo = "Magick2CPC";
    rev = "1f2b38a73a1c0833424eb5f29e070ee4242cc431";
    sha256 = "1w3rys5ayskga30frxxn7wps0igg4c3ld5yaysybs5kdhdq5zxmj";
  };

  nativeBuildInputs = [ autoreconfHook pkgconfig ];
  buildInputs = [ imagemagick ];

  meta = with stdenv.lib; {
    description = "An image converter for CPC using ImageMagick.";
    homepage = https://github.com/bignaux/Magick2CPC;
    license = licenses.gpl3;
    maintainers = with maintainers; [ genesis ];
    platforms = with platforms; linux; # possibly others, but only tested on Linux
  };
}
