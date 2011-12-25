#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_track *
mocksp_track_create(char *name, int num_artists, sp_artist **artists,
                    sp_album *album, int duration, int popularity,
                    int disc, int index, sp_error error, int loaded)
{
    sp_track *t;

    t = malloc(sizeof(sp_track));
    memset(t, 0, sizeof(sp_track));
    strcpy(t->name, name);
    t->loaded = loaded;
    t->disc = disc;
    t->index = index;
    t->error = error;
    t->duration = duration;
    t->popularity = popularity;
    t->album = album;
    t->starred = 0;
    return t;
}

/*** Spotify API ***/

sp_track_availability
sp_track_get_availability(sp_session *session, sp_track *t)
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
    return 3;
}

sp_artist *
sp_track_artist(sp_track *t, int index)
{
    static sp_artist *a[3];

    a[0] = mocksp_artist_create("a1", 1);
    a[1] = mocksp_artist_create("a2", 1);
    a[2] = mocksp_artist_create("a3", 1);
    return a[index];
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
sp_track_set_starred(sp_session *s, sp_track *const *ts, int n, bool starred)
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
