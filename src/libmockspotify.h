/*
 * API for libmockspotify
 *
 */


#ifndef LIBMOCKSPOTIFY_API_H
#define LIBMOCKSPOTIFY_API_H

#include <libspotify/api.h>
#include "util.h"

/*** Mock structures ***/

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
    char *full_name;
    char *picture;
    sp_relation_type relation;
};

struct sp_link {
    char data[1024];
};

/*** Mock object creation ***/

sp_album *
mocksp_album_create(char *name, sp_artist *artist, int year, byte *cover,
                    int type, int loaded, int available);

sp_albumbrowse *
mocksp_albumbrowse_create(sp_album *album, bool loaded);

sp_artist *
mocksp_artist_create(const char *name, int loaded);

sp_track *
mocksp_track_create(char *name, int num_artists, sp_artist ** artists,
                    sp_album * album, int duration, int popularity,
                    int disc, int index, sp_error error, int loaded);

sp_user *
mocksp_user_create(char *canonical_name, char *display_name, char *full_name,
                   char *picture, sp_relation_type relation, bool loaded);

#endif /* LIBMOCKSPOTIFY_API_H */
