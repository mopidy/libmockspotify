/*
 * API for libmockspotify
 *
 */


#ifndef LIBMOCKSPOTIFY_API_H
#define LIBMOCKSPOTIFY_API_H

#include <libspotify/api.h>

struct sp_artist {
    char name[1024];
    int loaded;
};

sp_artist *
mocksp_artist_create(const char *name, int loaded);

#endif /* LIBMOCKSPOTIFY_API_H */
