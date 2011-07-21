#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_playlistcontainer *
mocksp_playlistcontainer_create(void)
{
    sp_playlistcontainer *pc;

    pc = malloc(sizeof(sp_playlistcontainer));
    memset(pc, 0, sizeof(sp_playlistcontainer));
    return pc;
}

void
mocksp_playlistcontainer_event(event_type event, sp_playlistcontainer *c)
{
    sp_playlist *playlist = mocksp_playlist_create("foo");

    switch (event) {
    case MOCK_CONTAINER_LOADED:
        if (c->callbacks->container_loaded)
            c->callbacks->container_loaded(c, c->userdata);
        break;
    case MOCK_CONTAINER_PLAYLIST_ADDED:
        if (c->callbacks->playlist_added)
            c->callbacks->playlist_added(c, playlist, 0, c->userdata);
        break;
    case MOCK_CONTAINER_PLAYLIST_MOVED:
        if (c->callbacks->playlist_moved)
            c->callbacks->playlist_moved(c, playlist, 0, 1, c->userdata);
        break;
    case MOCK_CONTAINER_PLAYLIST_REMOVED:
        if (c->callbacks->playlist_removed)
            c->callbacks->playlist_removed(c, playlist, 0, c->userdata);
        break;
    default:
        break;
    }
}

/*** Spotify API ***/

void
sp_playlistcontainer_add_ref(sp_playlistcontainer *p)
{
}

void
sp_playlistcontainer_release(sp_playlistcontainer *p)
{
}

sp_playlist *
sp_playlistcontainer_playlist(sp_playlistcontainer *pc, int index)
{
    return pc->playlist[index];
}

int
sp_playlistcontainer_num_playlists(sp_playlistcontainer *pc)
{
    return pc->num_playlists;
}

void
sp_playlistcontainer_add_callbacks(sp_playlistcontainer *pc,
                                   sp_playlistcontainer_callbacks *cb,
                                   void *userdata)
{
    pc->callbacks = cb;
    pc->userdata = userdata;
}
