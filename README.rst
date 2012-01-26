**************
libmockspotify
**************

A mock of libspotify for use in development of language bindings.

This project was started in July 2011 with the goal of splitting out
pyspotify's mock of libspotify, so that it could be reused by the developers of
the Node.js and Ruby bindings for libspotify.

Coordination of the development efforts happens on GitHub and #spotify on
Freenode.


Installation
============

::

    $ ./autogen.sh
    $ ./configure
    $ make
    $ sudo make install


Changes
=======

v0.1 (in development)
---------------------

- Synced with pyspotify's mock of libspotify. libmockspotify is now compatible
  with libspotify 10.

- Merged the fork from Burgestrand/libmockspotify.

- Added event handling.

License
=======

libmockspotify is licensed under the Apache License, Version 2.0. A full copy
of the license may be found in the ``LICENSE`` file bundled with the software.
