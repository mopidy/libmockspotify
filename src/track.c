#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_track *
mocksp_track_create(const char *name, int num_artists, sp_artist **artists,
                    sp_album *album, int duration, int popularity,
                    int disc, int index, sp_error error, bool loaded)
{
    sp_track *t = ALLOC(sp_track);

    strcpy(t->name, name);
    t->loaded = loaded;
    t->disc = disc;
    t->index = index;
    t->error = error;
    t->duration = duration;
    t->popularity = popularity;
    t->album = album;
    t->starred = 0;

    t->artists = ALLOC_N(sp_artist*, num_artists);
    MEMCPY_N(t->artists, artists, sp_artist*, num_artists);
    t->num_artists = num_artists;

    return t;
}

/*** Spotify API ***/

sp_track *
sp_localtrack_create(const char *artist, const char *title, const char *album, int length)
{
  sp_artist *partist = mocksp_artist_create(artist, 1);
  sp_album  *palbum  = NULL;

  if (strlen(album) > 0)
  {
    palbum  = mocksp_album_create(album, partist, 2011, NULL, SP_ALBUMTYPE_UNKNOWN, 1, 1);
  }

  return mocksp_track_create(title, 1, &partist, palbum, length, 0, 0, 0, 0, 1);
}

bool
sp_track_is_available(sp_session *session, sp_track *t)
{
    return 1;
}

bool
sp_track_is_loaded(sp_track *t)
{
    return t->loaded;
}

const char *
sp_track_name(sp_track *track)
{
    return track->name;
}

int
sp_track_num_artists(sp_track *t)
{
    return t->num_artists;
}

sp_artist *
sp_track_artist(sp_track *t, int index)
{
    if (index >= sp_track_num_artists(t))
      return NULL;

    return t->artists[index];
}

int
sp_track_disc(sp_track *t)
{
    return t->disc;
}

int
sp_track_index(sp_track *t)
{
    return t->index;
}

int
sp_track_popularity(sp_track *t)
{
    return t->popularity;
}

int
sp_track_duration(sp_track *t)
{
    return t->duration;
}

sp_error
sp_track_error(sp_track *t)
{
    return t->error;
}

sp_album *
sp_track_album(sp_track *t)
{
    return t->album;
}

bool
sp_track_is_local(sp_session *s, sp_track *t)
{
    return 0;
}

bool
sp_track_is_starred(sp_session *s, sp_track *t)
{
    return t->starred;
}

void
sp_track_set_starred(sp_session *s, const sp_track **ts, int n, bool starred)
{
    int i;

    for (i = 0; i < n; i++)
        ((sp_track *) ts[i])->starred = starred;
}

void
sp_track_add_ref(sp_track *track)
{
}

void
sp_track_release(sp_track *track)
{
}
