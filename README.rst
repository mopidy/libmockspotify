libmockspotify
==============

A mock of libspotify for use in development of language bindings.

This project was started in July 2011 with the goal of splitting out
pyspotify's mock of libspotify, so that it could be reused by the developers of
the Node.js and Ruby bindings for libspotify.

Coordination of the development efforts happens on GitHub and #spotify on
Freenode.

Note about my fork
------------------
To ease usage in my own development, I’ve turned this project into a
Ruby gem. This allows you to install it as a gem, and also allows you
to retrieve the path to the compiled binary.

Installing it as a gem:

    gem install mockspotify

Using its’ API (one method):

    require 'mockspotify'
    MockSpotify.lib_path # => path/to/gem/src/libmockspotify.extension

You can then use this to bind this library using Ruby FFI:

    require 'ffi'
    require 'mockspotify'

    module Spotify
      extend FFI::Library
      ffi_lib MockSpotify.lib_path

      attach_function …, etc
    end

Installation
------------

::

    $ ./autogen.sh
    $ ./configure
    $ make
    # make install
