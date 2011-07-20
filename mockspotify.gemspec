# -*- encoding: utf-8 -*-
require File.expand_path('../lib/mockspotify', __FILE__)

Gem::Specification.new do |gem|
  gem.name     = "libmockspotify"
  gem.summary  = %Q{A mock of libspotify for use in development of language bindings}
  gem.homepage = "https://github.com/Burgestrand/libmockspotify"
  gem.authors  = ["Kim Burgestrand"]
  gem.email    = 'kim@burgestrand.se'

  gem.files         = `git ls-files`.split("\n")
  gem.executables   = []
  gem.require_paths = ["lib", "src"]
  gem.extensions    << 'src/extconf.rb'

  gem.version     = MockSpotify::VERSION
  gem.platform    = Gem::Platform::RUBY
end
