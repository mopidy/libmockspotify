#include "libmockspotify.h"

sp_search *
mocksp_search_create(sp_error error, const char *query, const char *did_you_mean,
                     int total_tracks, int num_tracks, const sp_track **tracks,
                     int total_albums, int num_albums, const sp_album **albums,
                     int total_artists, int num_artists, const sp_artist **artists,
                     search_complete_cb *callback, void *userdata)
{
  sp_search *search = ALLOC(sp_search);

  search->error = error;
  search->query = strclone(query);
  search->did_you_mean = strclone(did_you_mean);

  search->total_tracks  = total_tracks;
  search->total_artists = total_artists;
  search->total_albums  = total_albums;

  search->num_tracks  = num_tracks;
  search->num_artists = num_artists;
  search->num_albums  = num_albums;

  search->tracks  = ALLOC_N(sp_track *, num_tracks);
  search->artists = ALLOC_N(sp_artist *, num_artists);
  search->albums  = ALLOC_N(sp_album *, num_artists);

  MEMCPY_N(search->tracks, tracks, sp_track *, num_tracks);
  MEMCPY_N(search->artists, artists, sp_artist *, num_artists);
  MEMCPY_N(search->albums, albums, sp_album *, num_albums);

  search->callback = callback;
  search->userdata = userdata;

  return search;
}

DEFINE_REFCOUNTERS_FOR(search);

DEFINE_READER(search, query, const char *);
DEFINE_READER(search, did_you_mean, const char *);
DEFINE_READER(search, error, sp_error);

DEFINE_READER(search, num_artists, int);
DEFINE_ARRAY_READER(search, artist, sp_artist *);
DEFINE_READER(search, total_artists, int);

DEFINE_READER(search, num_albums, int);
DEFINE_ARRAY_READER(search, album, sp_album *);
DEFINE_READER(search, total_albums, int);

DEFINE_READER(search, num_tracks, int);
DEFINE_ARRAY_READER(search, track, sp_track *);
DEFINE_READER(search, total_tracks, int);

sp_search *
sp_search_create(sp_session *UNUSED(session), const char *query,
                 int UNUSED(tracks_offset), int UNUSED(tracks),
                 int UNUSED(albums_offset), int UNUSED(albums),
                 int UNUSED(artists_offset), int UNUSED(artists),
                 search_complete_cb *UNUSED(cb), void *UNUSED(userdata))
{
  char *searchquery = ALLOC_N(char, strlen("spotify:search:") + strlen(query) + 1);
  sprintf(searchquery, "spotify:search:%s", query);
  return (sp_search *)registry_find(searchquery);
}

sp_search *
sp_radio_search_create(sp_session *UNUSED(session),
                       unsigned int from_year, unsigned int to_year,
                       sp_radio_genre genres,
                       search_complete_cb *UNUSED(callback), void *UNUSED(userdata))
{
  char *searchquery = ALLOC_N(char, strlen("spotify:radio:deadbeef:1990-2011") + 1);
  sprintf(searchquery, "spotify:radio:%08x:%04d-%04d", genres, from_year, to_year);
  return (sp_search *)registry_find(searchquery);
}

bool
sp_search_is_loaded(sp_search *search)
{
  return search->error == SP_ERROR_OK;
}
