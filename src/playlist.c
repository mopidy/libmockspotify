#include "libmockspotify.h"

sp_playlist *
mocksp_playlist_create(const char *name)
{
  sp_playlist *playlist = ALLOC(sp_playlist);
  playlist->name = strclone(name);
  return playlist;
}

DEFINE_REFCOUNTERS_FOR(playlist);

DEFINE_READER(bool, playlist, is_loaded);
DEFINE_READER(const char *, playlist, name);
DEFINE_READER(int, playlist, num_tracks);
DEFINE_READER(bool, playlist, is_collaborative);

sp_error
sp_playlist_rename(sp_playlist *playlist, const char *new_name)
{
  playlist->name = strclone(new_name);
  return SP_ERROR_OK;
}

sp_track *
sp_playlist_track(sp_playlist *playlist, int index)
{
  return playlist->track[index];
}
