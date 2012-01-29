**************
libmockspotify
**************

A mock of libspotify for use in development of language bindings.

This project was split out of `pyspotify <http://pyspotify.mopidy.com/>`_, so
that it could be reused by the developers of other language bindings for
libspotify, such as the Node.js and Ruby bindings.

Coordination of the development efforts takes place on
`GitHub <https://github.com/mopidy/libmockspotify>`_.

A Debian package of libmockspotify is available from
`Mopidy's APT archive <http://apt.mopidy.com/>`_.


Installation
============

::

    $ ./autogen.sh
    $ ./configure
    $ make
    $ sudo make install


License
=======

libmockspotify is licensed under the Apache License, Version 2.0. A full copy
of the license may be found in the ``LICENSE`` file bundled with the software.


Authors
=======

A list of contributors to libmockspotify from the point where
the project was extracted from pyspotify is available at:

https://github.com/mopidy/libmockspotify/contributors


Changes
=======

v0.1 (in development)
---------------------

- Synced with pyspotify's mock of libspotify. libmockspotify is now compatible
  with libspotify 10.

- Merged the fork from Burgestrand/libmockspotify.

- Added event handling.
