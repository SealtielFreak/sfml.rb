require 'rake'
require_relative 'lib/sfml/version'

task default: 'all'

task :uninstall do
  system "gem uninstall sfml"
end

task :build do
  system "gem build sfml.gemspec"
end

task :install do
  system "gem install sfml-#{SFML::VERSION}.gem"
end

task :test do
  #system 'ruby test/hello-world.rb'
end

task :all do
  Rake::Task['uninstall'].invoke
  Rake::Task['build'].invoke
  Rake::Task['install'].invoke
end
