require 'mkmf'
require_relative 'auxlib.rb'

CHECK_PACKAGE = Arguments.include? 'install-package'
LIBS = {}
MODE_COMPILE = :generic

LIBS[:generic] = %w[
  csfml-graphics
  csfml-window
  csfml-system
  csfml-audio
]

if with_config('native') || true
  if try_cflags('-march=native')
    $CFLAGS << ' -march=native'
  elsif try_cflags('-mcpu=native')
    $CFLAGS << ' -mcpu=native'
  end
end

$CFLAGS << ' -O3' unless $CFLAGS.include?('-O')
if CHECK_PACKAGE
  if System.windows?
    run_script 'msys2.sh'
  else
    run_script 'linux.sh'
  end
end

check_sfml3_code = <<-C
  #include <SFML/Config.h>
  #if !defined(SFML_VERSION_MAJOR) || SFML_VERSION_MAJOR < 3
  #error "You need SFML 3"
  #endif
  int main() { return 0; }
C

if try_compile(check_sfml3_code)
  $defs.push("-DCSFML_V3")
else
  puts "ERROR: You need install SFML and CSFML version 3.0 or higher is required."
  exit 1
end

LIBS[MODE_COMPILE].each { |l| have_library(l) }

create_makefile 'ext'
