#include "libmockspotify.h"

sp_track *
mocksp_track_create(const char *name, int num_artists, sp_artist **artists, sp_album *album,
                    int duration, int popularity, int disc, int index, sp_error error,
                    bool is_loaded, bool is_available, bool is_local, bool is_autolinked,
                    bool is_starred)
{
  sp_track *track = ALLOC(sp_track);

  track->name          = strclone(name);
  track->album         = album;
  track->duration      = duration;
  track->popularity    = popularity;
  track->disc          = disc;
  track->index         = index;
  track->error         = error;
  track->is_loaded     = is_loaded;
  track->is_available  = is_available;
  track->is_local      = is_local;
  track->is_autolinked = is_autolinked;
  track->is_starred    = is_starred;

  track->artists       = ALLOC_N(sp_artist *, num_artists);
  track->num_artists = num_artists;
  MEMCPY_N(track->artists, artists, sp_artist*, num_artists);

  return track;
}

DEFINE_REFCOUNTERS_FOR(track);
DEFINE_READER(const char *, track, name);
DEFINE_READER(sp_album *, track, album);
DEFINE_READER(int, track, duration);
DEFINE_READER(int, track, popularity);
DEFINE_READER(int, track, disc);
DEFINE_READER(int, track, index);
DEFINE_READER(sp_error, track, error);
DEFINE_READER(bool, track, is_loaded);
DEFINE_SESSION_READER(bool, track, is_available);
DEFINE_SESSION_READER(bool, track, is_local);
DEFINE_SESSION_READER(bool, track, is_autolinked);
DEFINE_SESSION_READER(bool, track, is_starred);
DEFINE_READER(int, track, num_artists);

sp_track *
sp_localtrack_create(const char *artist, const char *title, const char *album, int length)
{
  sp_artist *partist = mocksp_artist_create(artist, true);
  sp_album  *palbum  = NULL;

  if (strlen(album) > 0)
  {
    palbum  = mocksp_album_create(album, partist, 2011, NULL, SP_ALBUMTYPE_UNKNOWN, 1, 1);
  }

  return mocksp_track_create(title, 1, &partist, palbum, length, 0, 0, 0, SP_ERROR_OK, true, true, true, false, false);
}



void
sp_track_set_starred(sp_session *session, sp_track *const *tracks, int num_tracks, bool starred)
{
  int i;

  for (i = 0; i < num_tracks; i++)
  {
    tracks[i]->is_starred = starred;
  }
}
