#include "libmockspotify.h"

sp_artistbrowse *
mocksp_artistbrowse_create(sp_error error, sp_artist *artist,
                           int num_portraits, const byte **portraits,
                           int num_tracks, sp_track **tracks,
                           int num_albums, sp_album **albums,
                           int num_similar_artists, sp_artist **similar_artists,
                           const char *biography, sp_artistbrowse_type type,
                           artistbrowse_complete_cb *cb, void *userdata)
{
  int i = 0;
  sp_artistbrowse *artistbrowse = ALLOC(sp_artistbrowse);

  artistbrowse->error = error;
  artistbrowse->artist = artist;

  artistbrowse->portraits     = ALLOC_N(byte *, num_portraits);
  artistbrowse->num_portraits = num_portraits;
  for (i = 0; i < num_portraits; ++i)
  {
    artistbrowse->portraits[i] = ALLOC_N(byte, 20); // image_id = 20 bytes
    MEMCPY_N(artistbrowse->portraits[i], portraits[i], byte, 20);
  }

  artistbrowse->tracks     = ALLOC_N(sp_track *, num_tracks);
  artistbrowse->num_tracks = num_tracks;
  MEMCPY_N(artistbrowse->tracks, tracks, sp_track *, num_tracks);

  artistbrowse->albums     = ALLOC_N(sp_album *, num_albums);
  artistbrowse->num_albums = num_albums;
  MEMCPY_N(artistbrowse->albums, albums, sp_album *, num_albums);

  artistbrowse->similar_artists     = ALLOC_N(sp_artist *, num_similar_artists);
  artistbrowse->num_similar_artists = num_similar_artists;
  MEMCPY_N(artistbrowse->similar_artists, similar_artists, sp_artist *, num_similar_artists);

  artistbrowse->biography = strclone(biography);
  artistbrowse->type      = type;

  artistbrowse->callback = cb;
  artistbrowse->userdata = userdata;

  return artistbrowse;
}

DEFINE_REFCOUNTERS_FOR(artistbrowse);
DEFINE_READER(artistbrowse, error, sp_error);
DEFINE_READER(artistbrowse, artist, sp_artist *);
DEFINE_READER(artistbrowse, num_portraits, int);
DEFINE_ARRAY_READER(artistbrowse, portrait, const byte *);
DEFINE_READER(artistbrowse, num_tracks, int);
DEFINE_ARRAY_READER(artistbrowse, track, sp_track *);
DEFINE_READER(artistbrowse, num_albums, int);
DEFINE_ARRAY_READER(artistbrowse, album, sp_album *);
DEFINE_READER(artistbrowse, num_similar_artists, int);
DEFINE_ARRAY_READER(artistbrowse, similar_artist, sp_artist *);
DEFINE_READER(artistbrowse, biography, const char *);

bool
sp_artistbrowse_is_loaded(sp_artistbrowse *artistbrowse)
{
  return artistbrowse->error == SP_ERROR_OK;
}

sp_artistbrowse *
sp_artistbrowse_create(sp_session *UNUSED(session), sp_artist *artist, sp_artistbrowse_type type, artistbrowse_complete_cb *callback, void *userdata)
{
  return mocksp_artistbrowse_create(SP_ERROR_OK, artist, 0, NULL, 0, NULL, 0, NULL, 0, NULL, "", type, callback, userdata);
}
