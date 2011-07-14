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

/*** Mock object creation ***/

sp_album *
mocksp_album_create(char *name, sp_artist *artist, int year, byte *cover,
                    int type, int loaded, int available);

sp_artist *
mocksp_artist_create(const char *name, int loaded);

#endif /* LIBMOCKSPOTIFY_API_H */
