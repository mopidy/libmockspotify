#include <stdlib.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_artistbrowse *
mock_artistbrowse_create(sp_artist * artist, bool loaded)
{
    sp_artistbrowse *ab;

    ab = malloc(sizeof(sp_artistbrowse));
    ab->loaded = loaded;
    ab->artist = artist;
    return ab;
}

/*** Spotify API ***/

void
sp_artistbrowse_add_ref(sp_artistbrowse * ab)
{
}

void
sp_artistbrowse_release(sp_artistbrowse * ab)
{
}

sp_artistbrowse *
sp_artistbrowse_create(sp_session * s, sp_artist * a,
                       artistbrowse_complete_cb cb, void *userdata)
{
    sp_artistbrowse *ab;

    ab = mock_artistbrowse_create(a, 1);
    if (cb)
        cb(ab, userdata);
    return ab;
}

sp_track *
sp_artistbrowse_track(sp_artistbrowse * ab, int index)
{
    sp_album *album;
    sp_track *track;

    album = mocksp_album_create("fool-album", ab->artist, 2001,
                        (byte *) "01234567890123456789", 1, 1, 1);
    switch (index) {
    case 0:
        track = mocksp_track_create("foo", 1, &(album->artist), album,
                            123, 0, 1, 1, SP_ERROR_OK, 1);
        break;
    case 1:
        track = mocksp_track_create("bar", 1, &(album->artist), album,
                            123, 0, 1, 2, SP_ERROR_OK, 1);
        break;
    case 2:
        track = mocksp_track_create("baz", 1, &(album->artist), album,
                            123, 0, 1, 3, SP_ERROR_OK, 1);
        break;
    default:
        track = NULL;
        break;
    }
    return track;
}

sp_album *
sp_artistbrowse_album(sp_artistbrowse * ab, int index)
{
    sp_album *album;

    switch (index) {
    case 0:
        album = mocksp_album_create("foo", ab->artist, 2001,
                            (byte *) "01234567890123456789", 1, 1, 1);
        break;
    case 1:
        album = mocksp_album_create("bar", ab->artist, 2002,
                            (byte *) "01234567890123456789", 1, 1, 1);
        break;
    case 2:
        album = mocksp_album_create("baz", ab->artist, 2003,
                            (byte *) "01234567890123456789", 1, 1, 1);
        break;
    default:
        album = NULL;
        break;
    }
    return album;
}

int
sp_artistbrowse_num_albums(sp_artistbrowse * ab)
{
    return 3;
}

int
sp_artistbrowse_num_tracks(sp_artistbrowse * ab)
{
    return 3;
}

bool
sp_artistbrowse_is_loaded(sp_artistbrowse * ab)
{
    return ab->loaded;
}
