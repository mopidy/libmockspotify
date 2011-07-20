require 'mockspotify'
require 'minitest/autorun'

describe Spotify::Mock do
  it "should define VERSION" do
    Spotify::Mock::VERSION.must_be_kind_of String
  end

  it "should provide a path to libmockspotify" do
    Spotify::Mock.path.must_be_kind_of String
    Spotify::Mock.path.must_match /libmockspotify\.(so|bundle)/
  end

  it "should have injected itself into Spotify's ancestor chain" do
    Spotify.singleton_class.ancestors.take(2).must_equal [Spotify::Mock, FFI::Library]
  end

  describe ".mock_artist" do
    before do
      @artist = Spotify.mock_artist "Bonkers", true
    end

    it "should have the proper name" do
      Spotify.artist_name(@artist).must_equal "Bonkers"
    end

    it "should have the proper load status" do
      Spotify.artist_is_loaded(@artist).must_equal true
    end
  end
end
