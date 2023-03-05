require 'mkmf-rice'

module System
  def System.name!
    RUBY_PLATFORM
  end

  def System.x64?
    (/x64/ =~ System.name!) != nil
  end

  def System.x686?
    (/686/ =~ System.name!) != nil
  end

  def System.windows?
    (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ System.name!) != nil
  end

  def System.mac?
    (/darwin/ =~ System.name!) != nil
  end

  def System.unix?
    !System.windows?
  end

  def System.linux?
    System.unix? and not System.mac?
  end

  def System.jruby?
    RUBY_ENGINE == 'jruby'
  end
end

def library_nofound
  raise 'You need install lib of SFML and Box2D in your system'
end

def run_script(filename)
  system "sh ./#{filename}"
end

module Arguments
  def Arguments.include?(flag)
    ARGV.include? flag
  end
end