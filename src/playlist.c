#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_playlist *
mocksp_playlist_create(const char *name)
{
    sp_playlist *p;

    p = ALLOC(sp_playlist);
    strcpy(p->name, name);
    return p;
}

void
mocksp_playlist_event(event_type event, sp_playlist *p)
{
    sp_artist *artist = mocksp_artist_create("foo_", 1);
    sp_album *album = mocksp_album_create("bar_", artist, 2011,
                                  (byte *) "01234567890123456789", 0, 1, 1);
    sp_user *user = mocksp_user_create("foo", "", "", "", 0, 0);
    sp_track *tracks[3] = {
        mocksp_track_create("foo", 1, &artist, album, 0, 0, 0, 0, 0, 1),
        mocksp_track_create("bar", 1, &artist, album, 0, 0, 0, 0, 0, 1),
        mocksp_track_create("baz", 1, &artist, album, 0, 0, 0, 0, 0, 1)
    };
    int nums[3] = { 0, 1, 2 };

    switch (event) {
    case MOCK_PLAYLIST_TRACKS_ADDED:
        if (p->callbacks->tracks_added)
            p->callbacks->tracks_added(p, tracks, 3, 0, p->userdata);
        break;
    case MOCK_PLAYLIST_TRACKS_MOVED:
        if (p->callbacks->tracks_moved)
            p->callbacks->tracks_moved(p, nums, 3, 0, p->userdata);
        break;
    case MOCK_PLAYLIST_TRACKS_REMOVED:
        if (p->callbacks->tracks_removed)
            p->callbacks->tracks_removed(p, nums, 3, p->userdata);
        break;

    case MOCK_PLAYLIST_RENAMED:
        if (p->callbacks->playlist_renamed)
            p->callbacks->playlist_renamed(p, p->userdata);
        break;

    case MOCK_PLAYLIST_STATE_CHANGED:
        if (p->callbacks->playlist_state_changed)
            p->callbacks->playlist_state_changed(p, p->userdata);
        break;

    case MOCK_PLAYLIST_UPDATE_IN_PROGRESS:
        if (p->callbacks->playlist_update_in_progress)
            p->callbacks->playlist_update_in_progress(p, 1, p->userdata);
        break;

    case MOCK_PLAYLIST_METADATA_UPDATED:
        if (p->callbacks->playlist_metadata_updated)
            p->callbacks->playlist_metadata_updated(p, p->userdata);
        break;

    case MOCK_PLAYLIST_TRACK_CREATED_CHANGED:
        if (p->callbacks->track_created_changed)
            p->callbacks->track_created_changed(p, 1, user, 123, p->userdata);
        break;

    case MOCK_PLAYLIST_TRACK_MESSAGE_CHANGED:
        if (p->callbacks->track_message_changed)
            p->callbacks->track_message_changed(p, 1, "foo", p->userdata);
        break;

    case MOCK_PLAYLIST_TRACK_SEEN_CHANGED:
        if (p->callbacks->track_seen_changed)
            p->callbacks->track_seen_changed(p, 1, 0, p->userdata);
        break;

    case MOCK_PLAYLIST_DESCRIPTION_CHANGED:
        if (p->callbacks->description_changed)
            p->callbacks->description_changed(p, "foo", p->userdata);
        break;

    case MOCK_PLAYLIST_SUBSCRIBERS_CHANGED:
        if (p->callbacks->subscribers_changed)
            p->callbacks->subscribers_changed(p, p->userdata);
        break;

    case MOCK_PLAYLIST_IMAGE_CHANGED:
        if (p->callbacks->image_changed)
            p->callbacks->image_changed(p, (byte *) "01234567890123456789",
                                        p->userdata);
        break;

    default:
        break;
    }
}

/*** Spotify API ***/

void
sp_playlist_add_ref(sp_playlist *p)
{
}

void
sp_playlist_release(sp_playlist *p)
{
}

void
sp_playlist_set_autolink_tracks(sp_playlist *p, bool set)
{
}

bool
sp_playlist_is_loaded(sp_playlist *p)
{
    return 1;
}

const char *
sp_playlist_name(sp_playlist *p)
{
    return p->name;
}

sp_error
sp_playlist_rename(sp_playlist *p, const char *new_name)
{
    strcpy(p->name, new_name);
    return SP_ERROR_OK;
}

sp_track *
sp_playlist_track(sp_playlist *p, int index)
{
    return p->track[index];
}

int
sp_playlist_num_tracks(sp_playlist *p)
{
    return p->num_tracks;
}

void
sp_playlist_add_callbacks(sp_playlist *p, sp_playlist_callbacks *cb,
                          void *userdata)
{
    p->callbacks = cb;
    p->userdata = userdata;
}

void
sp_playlist_remove_callbacks(sp_playlist *p, sp_playlist_callbacks *cb,
                             void *userdata)
{
    p->callbacks = NULL;
}

bool
sp_playlist_is_collaborative(sp_playlist *p)
{
    return 0;
}

sp_error
sp_playlist_remove_tracks(sp_playlist *p, const int *tracks, int num_tracks)
{
    // TODO
    return SP_ERROR_OK;
}
