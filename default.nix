with import <nixpkgs> { }; stdenv.mkDerivation rec {
  name = "magick2cpc";
  src = ./.;
  nativeBuildInputs = [ autoreconfHook pkgconfig ];
  buildInputs = [ imagemagick ];
}
