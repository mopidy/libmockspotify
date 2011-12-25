/*
 * API for libmockspotify
 *
 */


#ifndef LIBMOCKSPOTIFY_API_H
#define LIBMOCKSPOTIFY_API_H

#include <libspotify/api.h>

/*** Mock structures ***/

typedef struct {
    void *userdata;
    char username[1024];
    char password[1024];
    sp_session_config config;
    sp_playlist *starred;
    int bitrate;
} mocking_data;

extern mocking_data g_data;

struct sp_album {
    char name[1024];
    sp_artist *artist;
    int year;
    byte cover[20];
    int type;
    int loaded;
    bool available;
};

struct sp_albumbrowse {
    sp_album *album;
    int loaded;
};

struct sp_artist {
    char name[1024];
    int loaded;
};

struct sp_artistbrowse {
    sp_artist *artist;
    int loaded;
};

struct sp_image {
    /* TODO */
    int error;
};

struct sp_link {
    char data[1024];
};

struct sp_playlist {
    char name[1024];
    sp_track *track[32];
    int num_tracks;
    sp_playlist_callbacks *callbacks;
    void *userdata;
    sp_playlist_type type;
};

struct sp_playlistcontainer {
    sp_playlist *playlist[32];
    int num_playlists;
    sp_playlistcontainer_callbacks *callbacks;
    void *userdata;
};

struct sp_search {
    int loaded;
    int total_tracks;
    int num_tracks;
    int num_artists;
    int num_albums;
    sp_track *track[20];
    sp_album *album[20];
    sp_artist *artist[20];
    char *query;
    char *did_you_mean;
    int error;
};

struct sp_track {
    char name[1024];
    int num_artists;
    sp_artist *artists[16];
    sp_album *album;
    int duration;
    int popularity;
    int disc;
    int index;
    sp_error error;
    int loaded;
    int starred;
};

struct sp_user {
    bool loaded;
    char *canonical_name;
    char *display_name;
};

struct sp_toplistbrowse {
    bool                loaded;
    sp_toplisttype      type;
    sp_toplistregion    region;
    sp_album            *albums[3];
    sp_artist           *artists[3];
    sp_track            *tracks[3];
};

/*** Mock events ***/

typedef enum event_type {
    // SESSION EVENTS
    MOCK_LOGGED_IN = 0,
    MOCK_LOGGED_OUT = 1,
    MOCK_METADATA_UPDATED = 2,
    MOCK_CONNECTION_ERROR = 3,

    // PLAYLIST EVENTS
    MOCK_PLAYLIST_TRACKS_ADDED = 20,
    MOCK_PLAYLIST_TRACKS_MOVED = 21,
    MOCK_PLAYLIST_TRACKS_REMOVED = 22,
    MOCK_PLAYLIST_RENAMED = 23,
    MOCK_PLAYLIST_STATE_CHANGED = 24,
    MOCK_PLAYLIST_UPDATE_IN_PROGRESS = 25,
    MOCK_PLAYLIST_METADATA_UPDATED = 26,
    MOCK_PLAYLIST_TRACK_CREATED_CHANGED = 27,
    MOCK_PLAYLIST_TRACK_MESSAGE_CHANGED = 28,
    MOCK_PLAYLIST_TRACK_SEEN_CHANGED = 29,
    MOCK_PLAYLIST_DESCRIPTION_CHANGED = 30,
    MOCK_PLAYLIST_SUBSCRIBERS_CHANGED = 31,
    MOCK_PLAYLIST_IMAGE_CHANGED = 32,

    // CONTAINER EVENTS
    MOCK_CONTAINER_LOADED = 40,
    MOCK_CONTAINER_PLAYLIST_ADDED = 41,
    MOCK_CONTAINER_PLAYLIST_MOVED = 42,
    MOCK_CONTAINER_PLAYLIST_REMOVED = 43
} event_type;

void
mocksp_playlist_event(event_type event, sp_playlist *p);

void
mocksp_playlistcontainer_event(event_type event, sp_playlistcontainer *c);

/*** Mock object creation ***/

sp_album *
mocksp_album_create(char *name, sp_artist *artist, int year, byte *cover,
                    int type, int loaded, int available);

sp_albumbrowse *
mocksp_albumbrowse_create(sp_album *album, bool loaded);

sp_artist *
mocksp_artist_create(const char *name, int loaded);

sp_artistbrowse *
mocksp_artistbrowse_create(sp_artist *artist, bool loaded);

sp_playlist *
mocksp_playlist_create(char *name);

sp_playlistcontainer *
mocksp_playlistcontainer_create(void);

sp_track *
mocksp_track_create(char *name, int num_artists, sp_artist ** artists,
                    sp_album * album, int duration, int popularity,
                    int disc, int index, sp_error error, int loaded);

sp_user *
mocksp_user_create(char *canonical_name, char *display_name, bool loaded);

#endif /* LIBMOCKSPOTIFY_API_H */
