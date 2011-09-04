#include "libmockspotify.h"

sp_album *
mocksp_album_create(const char *name, sp_artist *artist, int year, const byte *cover,
                    sp_albumtype type, bool loaded, bool available)
{
  sp_album *album = ALLOC(sp_album);

  album->name         = strclone(name);
  album->year         = year;
  album->type         = type;
  album->artist       = artist;
  album->is_loaded    = loaded;
  album->is_available = available;

  if (cover)
  {
    MEMCPY_N(album->cover, cover, byte, 20);
  }

  return album;
}

DEFINE_REFCOUNTERS_FOR(album);

DEFINE_READER(bool, album, is_loaded);
DEFINE_READER(bool, album, is_available);
DEFINE_READER(sp_artist *, album, artist);
DEFINE_READER(const byte *, album, cover);
DEFINE_READER(const char *, album, name);
DEFINE_READER(int, album, year);
DEFINE_READER(sp_albumtype, album, type);
