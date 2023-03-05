#!/usr/bin/sh

curl -O https://repo.msys2.org/msys/x86_64/msys2-keyring-r21.b39fb11-1-any.pkg.tar.xz;
curl -O https://repo.msys2.org/msys/x86_64/msys2-keyring-r21.b39fb11-1-any.pkg.tar.xz.sig;

pacman-key --verify msys2-keyring-r21.b39fb11-1-any.pkg.tar.xz.sig;
pacman -U msys2-keyring-r21.b39fb11-1-any.pkg.tar.xz;

pacman -U --config <(echo) msys2-keyring-r21.b39fb11-1-any.pkg.tar.xz;

pacman -Syy;

if $(uname -m | grep '64'); then
  #pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-csfml --noconfirm
  pacman -Sy mingw-w64-x86_64-csfml --noconfirm;
else
  #pacman -S mingw-w64-i686-gcc mingw-w64-i686-csfml --noconfirm
  pacman -Sy mingw-w64-i686-csfml --noconfirm;
fi