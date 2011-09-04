#include "libmockspotify.h"

sp_search *
sp_search_create(sp_session *session, const char *query, int track_offset,
                 int track_count, int album_offset, int album_count, int artist_offset,
                 int artist_count, search_complete_cb *callback, void *userdata)
{
  return NULL; /* TODO */
}

DEFINE_REFCOUNTERS_FOR(search);

DEFINE_READER(const char *, search, query);
DEFINE_READER(const char *, search, did_you_mean);
DEFINE_READER(sp_error, search, error);
DEFINE_READER(bool, search, is_loaded);
DEFINE_READER(int, search, num_artists);
DEFINE_READER(int, search, num_albums);
DEFINE_READER(int, search, num_tracks);
DEFINE_READER(int, search, total_tracks);
