#include "libmockspotify.h"

sp_artist *
mocksp_artist_create(const char *name, bool is_loaded)
{
  sp_artist *artist = ALLOC(sp_artist);
  artist->name      = strclone(name);
  artist->is_loaded = is_loaded;
  return artist;
}

DEFINE_REFCOUNTERS_FOR(artist);
DEFINE_READER(const char *, artist, name);
DEFINE_READER(bool, artist, is_loaded);
