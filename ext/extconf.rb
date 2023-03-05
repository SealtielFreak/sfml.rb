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

if CHECK_PACKAGE
  puts 'Installing dependencies...'

  if System.windows?
    run_script 'msys2.sh'
  else
    run_script 'linux.sh'
  end
end

LIBS[MODE_COMPILE].each { |l| have_library(l) }

create_makefile 'ext'
