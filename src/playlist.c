#include "libmockspotify.h"

sp_playlist *
mocksp_playlist_create(const char *name, bool is_loaded, sp_user *owner, bool is_collaborative,
                       const char *description, const byte *image, bool has_pending_changes,
                       unsigned int num_subscribers, sp_subscribers *subscribers, bool is_in_ram,
                       sp_playlist_offline_status offline_status, int offline_download_completed,
                       int num_tracks, sp_playlist_track_t *tracks)
{
  int i;
  sp_playlist *playlist = ALLOC(sp_playlist);

  playlist->name = strclone(name);
  playlist->is_loaded = is_loaded;
  playlist->owner = owner;
  playlist->is_collaborative = is_collaborative;
  playlist->get_description = strclone(description);
  MEMCPY_N(playlist->image, image, byte, 20);
  playlist->has_pending_changes = has_pending_changes;

  playlist->num_subscribers = num_subscribers;
  playlist->subscribers     = subscribers;

  playlist->is_in_ram = is_in_ram;
  playlist->get_offline_status = offline_status;
  playlist->get_offline_download_completed = offline_download_completed;

  playlist->num_tracks = num_tracks;
  playlist->tracks     = ALLOC_N(sp_playlist_track_t, num_tracks);
  MEMCPY_N(playlist->tracks, tracks, sp_playlist_track_t, num_tracks);

  /* private mock accessors */
  playlist->autolink_tracks = false;

  return playlist;
}

sp_subscribers *
mocksp_subscribers(int count, char **names)
{
  int i = 0;

  sp_subscribers *subscribers = (sp_subscribers *) malloc(sizeof(sp_subscribers) + sizeof(char*) * (count - 1));
  subscribers->count = count;

  for (i = 0; i < count; ++i)
  {
    subscribers->subscribers[i] = strclone(names[i]);
  }

  return subscribers;
}

void
sp_playlist_subscribers_free(sp_subscribers *subscribers)
{
  unsigned int i;

  for (i = 0; i < subscribers->count; ++i)
  {
    free(subscribers->subscribers[i]);
  }

  free(subscribers);
}

DEFINE_REFCOUNTERS_FOR(playlist);

DEFINE_READER(playlist, name, const char *);
DEFINE_READER(playlist, is_loaded, bool);
DEFINE_READER(playlist, num_tracks, int);
DEFINE_READER(playlist, is_collaborative, bool);
DEFINE_READER(playlist, has_pending_changes, bool);
DEFINE_READER(playlist, owner, sp_user *);
DEFINE_READER(playlist, get_description, const char *);
DEFINE_READER(playlist, subscribers, sp_subscribers *);
DEFINE_READER(playlist, num_subscribers, unsigned int);
DEFINE_SESSION_READER(playlist, get_offline_status, sp_playlist_offline_status);
DEFINE_SESSION_READER(playlist, get_offline_download_completed, int);
DEFINE_SESSION_READER(playlist, is_in_ram, bool);

DEFINE_ARRAY_MEMBER_READER(playlist, track, track, sp_track *);
DEFINE_ARRAY_MEMBER_READER(playlist, track, create_time, int);
DEFINE_ARRAY_MEMBER_READER(playlist, track, creator, sp_user *);
DEFINE_ARRAY_MEMBER_READER(playlist, track, message, const char *);
DEFINE_ARRAY_MEMBER_READER(playlist, track, seen, bool);

DEFINE_MOCK_READER(playlist, autolink_tracks, bool);

sp_playlist *
sp_playlist_create(sp_session *session, sp_link *link)
{
  sp_linktype type = sp_link_type(link);

  if (type != SP_LINKTYPE_PLAYLIST && type != SP_LINKTYPE_STARRED)
  {
    return NULL;
  }

  return registry_find(link->data);
}

sp_track *
sp_playlist_track(sp_playlist *playlist, int index)
{
  return sp_playlist_track_track(playlist, index);
}

sp_error
sp_playlist_track_set_seen(sp_playlist *playlist, int index, bool seen)
{
  if (index >= playlist->num_tracks)
  {
    return SP_ERROR_INDEX_OUT_OF_RANGE;
  }

  playlist->tracks[index].seen = seen;
  return SP_ERROR_OK;
}

bool
sp_playlist_get_image(sp_playlist *playlist, byte *buffout)
{
  if (playlist->image)
  {
    MEMCPY_N(buffout, playlist->image, byte, 20);
    return true;
  }

  return false;
}

sp_error
sp_playlist_rename(sp_playlist *playlist, const char *new_name)
{
  playlist->name = strclone(new_name);
  return SP_ERROR_OK;
}

void
sp_playlist_set_collaborative(sp_playlist *playlist, bool collaborative)
{
  playlist->is_collaborative = collaborative;
}

void
sp_playlist_set_autolink_tracks(sp_playlist *playlist, bool autolink_tracks)
{
  playlist->autolink_tracks = autolink_tracks;
}

void
sp_playlist_set_in_ram(sp_session *session, sp_playlist *playlist, bool in_ram)
{
  playlist->is_in_ram = in_ram;
}

void
sp_playlist_set_offline_mode(sp_session *session, sp_playlist *playlist, bool offline_mode)
{
  playlist->get_offline_status = SP_PLAYLIST_OFFLINE_STATUS_YES;
}

void
sp_playlist_add_callbacks(sp_playlist *playlist, sp_playlist_callbacks *callbacks, void *userdata)
{
  playlist->callbacks = callbacks;
  playlist->userdata  = userdata;
}

void
sp_playlist_remove_callbacks(sp_playlist *playlist, sp_playlist_callbacks *callbacks, void *userdata)
{
  playlist->callbacks = NULL;
  playlist->userdata  = NULL;
}

void
sp_playlist_update_subscribers(sp_session *session, sp_playlist *playlist)
{
  if (playlist->callbacks && playlist->callbacks->subscribers_changed)
  {
    playlist->callbacks->subscribers_changed(playlist, playlist->userdata);
  }
}
