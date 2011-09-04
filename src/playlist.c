#include "libmockspotify.h"

sp_playlist *
mocksp_playlist_create(const char *name)
{
  sp_playlist *playlist = ALLOC(sp_playlist);
  playlist->name = strclone(name);
  return playlist;
}

DEFINE_REFCOUNTERS_FOR(playlist);

DEFINE_READER(playlist, is_loaded, bool);
DEFINE_READER(playlist, name, const char *);
DEFINE_READER(playlist, num_tracks, int);
DEFINE_READER(playlist, is_collaborative, bool);

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
