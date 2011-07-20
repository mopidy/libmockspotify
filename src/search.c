#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** Spotify API ***/

void
sp_search_add_ref(sp_search *search)
{
}

void
sp_search_release(sp_search *search)
{
}

sp_search *
sp_search_create(sp_session *session, const char *query, int track_offset,
                 int track_count, int album_offset, int album_count,
                 int artist_offset, int artist_count,
                 search_complete_cb *callback, void *userdata)
{
    sp_search *search = ALLOC(sp_search);

    if (!strncmp(query, "!loaded", 7))
        search->loaded = 0;
    if (!strncmp(query, "loaded", 6))
        search->loaded = 1;
    search->num_tracks = 4;
    search->num_albums = 3;
    search->num_artists = 2;
    search->total_tracks = 24;
    search->query = ALLOC_N(char, strlen(query) + 1);
    strcpy(search->query, query);
    search->error = 3;
    search->did_you_mean = ALLOC_N(char, strlen("did_you_mean") + 1);
    sprintf(search->did_you_mean, "did_you_mean");
    search->artist[0] = mocksp_artist_create("foo", 1);
    search->artist[1] = mocksp_artist_create("bar", 1);
    search->album[0] = mocksp_album_create("baz", search->artist[0], 2001,
                                           (byte *) "01234567890123456789",
                                           1, 1, 1);
    search->album[1] = mocksp_album_create("qux", search->artist[1], 2002,
                                           (byte *) "01234567890123456789",
                                           1, 1, 1);
    search->album[2] = mocksp_album_create("quux", search->artist[0], 2003,
                                           (byte *) "01234567890123456789",
                                           1, 1, 1);
    search->track[0] =
        mocksp_track_create("corge", 1, search->artist, search->album[0],
                            99, 72, 1, 1, 0, 1);
    search->track[1] =
        mocksp_track_create("grault", 1, search->artist, search->album[1],
                            98, 72, 1, 1, 0, 1);
    search->track[2] =
        mocksp_track_create("garply", 1, search->artist, search->album[2],
                            97, 72, 1, 1, 0, 1);
    search->track[3] =
        mocksp_track_create("waldo", 1, search->artist, search->album[0],
                            96, 72, 1, 1, 0, 1);
    callback(search, userdata);
    return search;
}

bool
sp_search_is_loaded(sp_search *s)
{
    return s->loaded;
}

int
sp_search_num_artists(sp_search *s)
{
    return s->num_artists;
}

int
sp_search_num_albums(sp_search *s)
{
    return s->num_albums;
}

int
sp_search_num_tracks(sp_search *s)
{
    return s->num_tracks;
}

int
sp_search_total_tracks(sp_search *s)
{
    return s->total_tracks;
}

sp_artist *
sp_search_artist(sp_search *s, int i)
{
    return s->artist[i];
}

sp_album *
sp_search_album(sp_search *s, int i)
{
    return s->album[i];
}

sp_track *
sp_search_track(sp_search *s, int i)
{
    return s->track[i];
}

const char *
sp_search_query(sp_search *s)
{
    return s->query;
}

sp_error
sp_search_error(sp_search *s)
{
    return s->error;
}

const char *
sp_search_did_you_mean(sp_search *s)
{
    return s->did_you_mean;
}
