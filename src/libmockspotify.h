/*
 * API for libmockspotify
 *
 */


#ifndef LIBMOCKSPOTIFY_API_H
#define LIBMOCKSPOTIFY_API_H

#include <libspotify/api.h>

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

/*** Mock object creation ***/

sp_album *
mocksp_album_create(char *name, sp_artist *artist, int year, byte *cover,
                    int type, int loaded, int available);

sp_artist *
mocksp_artist_create(const char *name, int loaded);

sp_track *
mocksp_track_create(char *name, int num_artists, sp_artist ** artists,
                    sp_album * album, int duration, int popularity,
                    int disc, int index, sp_error error, int loaded);

#endif /* LIBMOCKSPOTIFY_API_H */
