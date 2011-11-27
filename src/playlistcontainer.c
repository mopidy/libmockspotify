#include "libmockspotify.h"

static sp_error
mocksp_playlistcontainer_insert(sp_playlistcontainer *, int, sp_playlistcontainer_playlist_t);

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
  int null_byte_index = 0;

  if (index >= pc->num_playlists)
  {
    return SP_ERROR_INDEX_OUT_OF_RANGE;
  }

  if (pc->playlists[index].folder_name)
  {
    strncpy(buffer, pc->playlists[index].folder_name, buffer_size);

    if (buffer_size <= strlen(pc->playlists[index].folder_name))
    {
      null_byte_index = buffer_size - 1;
    }
    else
    {
      null_byte_index = strlen(pc->playlists[index].folder_name);
    }
  }

  buffer[null_byte_index] = '\0';

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

static sp_error
mocksp_playlistcontainer_insert(sp_playlistcontainer *pc, int index, sp_playlistcontainer_playlist_t playlist)
{
  sp_playlistcontainer_playlist_t *new_playlists;
  int num_playlists = sp_playlistcontainer_num_playlists(pc);
  int new_num_playlists = num_playlists + 1;
  int i, j;

  if (index > num_playlists)
  {
    return SP_ERROR_INDEX_OUT_OF_RANGE;
  }

  new_playlists = ALLOC_N(sp_playlistcontainer_playlist_t, new_num_playlists);
  for (i = 0, j = 0; i < new_num_playlists; i++)
  {
    if (i == index)
    {
      MEMCPY(&new_playlists[i], &playlist, sp_playlistcontainer_playlist_t);
    }
    else
    {
      MEMCPY(&new_playlists[i], &pc->playlists[j++], sp_playlistcontainer_playlist_t);
    }
  }

  free(pc->playlists);
  pc->playlists = new_playlists;
  pc->num_playlists = new_num_playlists;

  return SP_ERROR_OK;
}

sp_playlist *
sp_playlistcontainer_add_new_playlist(sp_playlistcontainer *pc, const char *name)
{
  sp_playlist *playlist = mocksp_playlist_create(name, true, NULL, false, NULL, NULL, false, 0, NULL, true, SP_PLAYLIST_OFFLINE_STATUS_NO, 0, 0, NULL);

  sp_playlistcontainer_playlist_t container_playlist;
  container_playlist.playlist = playlist;
  container_playlist.type     = SP_PLAYLIST_TYPE_PLAYLIST;

  mocksp_playlistcontainer_insert(pc, sp_playlistcontainer_num_playlists(pc), container_playlist);

  return playlist;
}

sp_playlist *
sp_playlistcontainer_add_playlist(sp_playlistcontainer *pc, sp_link *link)
{
  sp_playlist *playlist = NULL;

  switch (sp_link_type(link))
  {
    case SP_LINKTYPE_PLAYLIST:
    case SP_LINKTYPE_STARRED:
      playlist = (sp_playlist *)registry_find(link->data);
      break;

    default: return NULL;
  }

  if (playlist)
  {
    sp_playlistcontainer_playlist_t container_playlist;

    container_playlist.playlist = playlist;
    container_playlist.type     = SP_PLAYLIST_TYPE_PLAYLIST;

    mocksp_playlistcontainer_insert(pc, sp_playlistcontainer_num_playlists(pc), container_playlist);
  }

  return playlist;
}

sp_error
sp_playlistcontainer_add_folder(sp_playlistcontainer *pc, int index, const char *name)
{
  sp_playlistcontainer_playlist_t start_folder;
  sp_playlistcontainer_playlist_t end_folder;
  long folder_id = random();

  start_folder.folder_id   = folder_id;
  start_folder.folder_name = strclone(name);
  start_folder.type        = SP_PLAYLIST_TYPE_START_FOLDER;

  end_folder.folder_id   = folder_id;
  end_folder.folder_name = "";
  end_folder.type        = SP_PLAYLIST_TYPE_END_FOLDER;

  sp_error error = mocksp_playlistcontainer_insert(pc, index, start_folder);

  if (error == SP_ERROR_OK)
  {
    error = mocksp_playlistcontainer_insert(pc, index + 1, end_folder);
  }

  return error;
}

/*
playlistcontainer_remove_playlist
playlistcontainer_move_playlist
*/
