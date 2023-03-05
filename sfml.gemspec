require_relative 'lib/sfml/version'

Gem::Specification.new do |s|
    s.name        = 'sfml'
    s.version     = SFML::VERSION
    s.summary     = 'SFML wrappe for Ruby'
    s.description = ''
    s.homepage    = 'https://github.com/sfml.rb/'
    
    s.authors     = ['Sealtiel Valderrama']
    s.email       = 'SealtielFreak@yandex.com'
    s.license     = 'LGPL-2.1'

    s.required_ruby_version = '>= 2.5.0'

    s.files       = Dir.glob('ext/**/*.{h,c,rb,sh}') +
                    Dir.glob('lib/**/*.{rb}') +
                    Dir.glob('test/**/*.{rb,png,otf}') +
                    Dir.glob('bin/**/*.{rb}') +
                    Dir.glob('assets/**/*.{otf}')

    s.extensions  = ['ext/extconf.rb']
end
