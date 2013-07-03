*******************
DEPRECATION WARNING
*******************

As of 2013-07-03 libmockspotify is merged back into pyspotify. It will no
longer be maintained an independent project.


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

v0.3.1 (2012-12-04)
-------------------

Supports libspotify 12

- Call ``notify_main_thread`` callback if set.
- Call ``logged_out`` callback if set.

v0.3 (2012-11-02)
-----------------

Supports libspotify 12.

- Updated signature of:

  - ``sp_link_create_from_album_cover()``,
  - ``sp_link_create_from_artist_portrait()``,
  - ``sp_album_cover()``, nad
  - ``sp_artist_portrait()``.

- Changed a lot of functions from returning ``void`` to returning ``sp_error``.

- Bumped SONAME to 2.

v0.2 (2012-04-21)
-----------------

Supports libspotify 11.

- Merged Burgestrand's work:

  - Have toplistbrowse_create lookup spotify:toplist:user:<username>:<type>
  - Add quick and dirty urlencoding/decoding to Search links
  - Add artist top tracks to artistbrowse
  - Add track_get_playable
  - Add playlistcontainer unseen/seen tracks
  - Fix playlists with no images
  - Make it possible to have albums with no cover link at all
  - Fix link creation from objects
  - Allow image to be allocated with no data
  - Make search_did_you_mean optional
  - Fix session offline sync status getter

- Bumped SONAME to 1.

v0.1 (2012-01-29)
-----------------

Supports libspotify 10.

- Synced with pyspotify's mock of libspotify. libmockspotify is now compatible
  with libspotify 10.

- Merged the fork from Burgestrand/libmockspotify.

- Added event handling.
