#include "libmockspotify.h"

sp_search *
sp_search_create(sp_session *session, const char *query, int track_offset,
                 int track_count, int album_offset, int album_count, int artist_offset,
                 int artist_count, search_complete_cb *callback, void *userdata)
{
  return NULL; /* TODO */
}

DEFINE_REFCOUNTERS_FOR(search);

DEFINE_READER(search, query, const char *);
DEFINE_READER(search, did_you_mean, const char *);
DEFINE_READER(search, error, sp_error);
DEFINE_READER(search, is_loaded, bool);
DEFINE_READER(search, num_artists, int);
DEFINE_READER(search, num_albums, int);
DEFINE_READER(search, num_tracks, int);
DEFINE_READER(search, total_tracks, int);
