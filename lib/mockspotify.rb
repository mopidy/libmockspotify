require 'rbconfig'

module MockSpotify
  VERSION = "0.0.1"

  class << self
    def lib_path
      File.expand_path('../../src/libmockspotify.', __FILE__) << RbConfig::CONFIG['DLEXT']
    end
  end
end
