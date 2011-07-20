require 'mockspotify'
require 'minitest/autorun'

describe MockSpotify do
  it "should define VERSION" do
    MockSpotify::VERSION.must_be_kind_of String
  end

  it "should provide a path to libmockspotify" do
    File.exist?(MockSpotify.lib_path).must_equal true
  end
end
