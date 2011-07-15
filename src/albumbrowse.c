#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_albumbrowse *
mocksp_albumbrowse_create(sp_album *album, bool loaded)
{
    sp_albumbrowse *ab;

    ab = malloc(sizeof(sp_albumbrowse));
    ab->loaded = loaded;
    ab->album = album;
    return ab;
}

/*** Spotify API ***/

void
sp_albumbrowse_add_ref(sp_albumbrowse *ab)
{
}

void
sp_albumbrowse_release(sp_albumbrowse *ab)
{
}

sp_track *
sp_albumbrowse_track(sp_albumbrowse *ab, int index)
{
    sp_track *track;

    switch (index) {
    case 0:
        track = mocksp_track_create("foo", 1, &(ab->album->artist), ab->album,
                                    123, 0, 1, 1, SP_ERROR_OK, 1);
        break;
    case 1:
        track = mocksp_track_create("bar", 1, &(ab->album->artist), ab->album,
                                    123, 0, 1, 2, SP_ERROR_OK, 1);
        break;
    case 2:
        track = mocksp_track_create("baz", 1, &(ab->album->artist), ab->album,
                                    123, 0, 1, 3, SP_ERROR_OK, 1);
        break;
    default:
        track = NULL;
        break;
    }
    return track;
}

int
sp_albumbrowse_num_tracks(sp_albumbrowse *ab)
{
    return 3;
}

bool
sp_albumbrowse_is_loaded(sp_albumbrowse *ab)
{
    return ab->loaded;
}

sp_albumbrowse *
sp_albumbrowse_create(sp_session *s, sp_album *a,
                      albumbrowse_complete_cb cb, void *userdata)
{
    sp_albumbrowse *ab;

    ab = mocksp_albumbrowse_create(a, 1);
    if (cb)
        cb(ab, userdata);
    return ab;
}
