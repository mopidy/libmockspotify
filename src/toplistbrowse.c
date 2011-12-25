#include <stdlib.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/


/*** Spotify API ***/
void
sp_toplistbrowse_add_ref(sp_toplistbrowse *tb)
{
}

void
sp_toplistbrowse_release(sp_toplistbrowse *tb)
{
}

bool
sp_toplistbrowse_is_loaded(sp_toplistbrowse *tb)
{
    return tb->loaded;
}

sp_error
sp_toplistbrowse_error(sp_toplistbrowse *tb)
{
    return SP_ERROR_OK;
}

int
sp_toplistbrowse_num_albums(sp_toplistbrowse *tb)
{
    return tb->type == SP_TOPLIST_TYPE_ALBUMS ? 3 : 0;
}

int
sp_toplistbrowse_num_artists(sp_toplistbrowse *tb)
{
    return tb->type == SP_TOPLIST_TYPE_ARTISTS ? 3 : 0;
}

int
sp_toplistbrowse_num_tracks(sp_toplistbrowse *tb)
{
    return tb->type == SP_TOPLIST_TYPE_TRACKS ? 3 : 0;
}

sp_album *
sp_toplistbrowse_album(sp_toplistbrowse *tb, int index)
{
    return tb->albums[index];
}

sp_artist *
sp_toplistbrowse_artist(sp_toplistbrowse *tb, int index)
{
    return tb->artists[index];
}

sp_track *
sp_toplistbrowse_track(sp_toplistbrowse *tb, int index)
{
    return tb->tracks[index];
}

sp_toplistbrowse *
sp_toplistbrowse_create(sp_session *session,
                        sp_toplisttype type, sp_toplistregion region,
                        const char *username,
                        toplistbrowse_complete_cb *cb, void *userdata)
{
    sp_toplistbrowse *tb;

    tb = (sp_toplistbrowse *)malloc(sizeof(struct sp_toplistbrowse));
    tb->albums[0] = mocksp_album_create("foo", NULL, 2001,
                                        (byte *) "01234567890123456789",
                                        1, 1, 1);
    tb->albums[1] = mocksp_album_create("bar", NULL, 2001,
                                        (byte *) "01234567890123456789",
                                        1, 1, 1);
    tb->albums[2] = mocksp_album_create("baz", NULL, 2001,
                                        (byte *) "01234567890123456789",
                                        1, 1, 1);
    tb->artists[0] = mocksp_artist_create("foo", 1);
    tb->artists[1] = mocksp_artist_create("bar", 1);
    tb->artists[2] = mocksp_artist_create("baz", 1);
    tb->tracks[0] = mocksp_track_create("foo", 1, NULL, NULL, 5, 0, 1, 1,
                                                                SP_ERROR_OK, 1);
    tb->tracks[1] = mocksp_track_create("bar", 1, NULL, NULL, 5, 0, 1, 1,
                                                                SP_ERROR_OK, 1);
    tb->tracks[2] = mocksp_track_create("baz", 1, NULL, NULL, 5, 0, 1, 1,
                                                                SP_ERROR_OK, 1);
    tb->type = type;
    tb->region = region;
    tb->loaded = 1;
    cb(tb, userdata);
    return tb;
}
