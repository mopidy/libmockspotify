#include "libmockspotify.h"

sp_playlistcontainer *
mocksp_playlistcontainer_create(sp_user *owner, bool loaded,
                                int num_playlists, sp_playlistcontainer_playlist_t *playlists,
                                sp_playlistcontainer_callbacks *callbacks, void *userdata)
{
  sp_playlistcontainer *container = ALLOC(sp_playlistcontainer);

  container->is_loaded = loaded;
  container->owner     = owner;

  container->num_playlists = num_playlists;
  container->playlists = ALLOC_N(sp_playlistcontainer_playlist_t, num_playlists);
  MEMCPY_N(container->playlists, playlists, sp_playlistcontainer_playlist_t, num_playlists);

  container->callbacks = callbacks;
  container->userdata  = userdata;

  return container;
}

DEFINE_REFCOUNTERS_FOR(playlistcontainer);

DEFINE_READER(playlistcontainer, is_loaded, bool);
DEFINE_READER(playlistcontainer, owner, sp_user *);
DEFINE_READER(playlistcontainer, num_playlists, int);
DEFINE_ARRAY_MEMBER_READER(playlistcontainer, playlist, playlist, sp_playlist *);
DEFINE_ARRAY_MEMBER_READER(playlistcontainer, playlist, type, sp_playlist_type);
DEFINE_ARRAY_MEMBER_READER(playlistcontainer, playlist, folder_id, sp_uint64);

sp_playlist *
sp_playlistcontainer_playlist(sp_playlistcontainer *pc, int index)
{
  return sp_playlistcontainer_playlist_playlist(pc, index);
}

sp_error
sp_playlistcontainer_playlist_folder_name(sp_playlistcontainer *pc, int index, char *buffer, int buffer_size)
{
  if (index >= pc->num_playlists)
  {
    return SP_ERROR_INDEX_OUT_OF_RANGE;
  }

  strncpy(buffer, pc->playlists[index].folder_name, buffer_size);

  if (buffer_size > 0)
  {
    buffer[buffer_size - 1] = '\0';
  }

  return SP_ERROR_OK;
}

void
sp_playlistcontainer_add_callbacks(sp_playlistcontainer *pc, sp_playlistcontainer_callbacks *callbacks, void *userdata)
{
  /* TODO: multi-callback support */
  pc->callbacks = callbacks;
  pc->userdata  = userdata;
}

void
sp_playlistcontainer_remove_callbacks(sp_playlistcontainer *pc, sp_playlistcontainer_callbacks *UNUSED(callbacks), void *UNUSED(userdata)) 
{
  /* TODO: multi-callback support */
  pc->callbacks = NULL;
  pc->userdata  = NULL;
}

/*
playlistcontainer_add_new_playlist
playlistcontainer_add_playlist
playlistcontainer_remove_playlist
playlistcontainer_move_playlist
playlistcontainer_add_folder
*/
