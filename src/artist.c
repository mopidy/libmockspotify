#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_artist *
mocksp_artist_create(const char *name, int loaded)
{
    sp_artist *a = ALLOC(sp_artist);
    strcpy(a->name, name);
    a->loaded = loaded;
    return a;
}

/*** Spotify API ***/

void
sp_artist_add_ref(sp_artist *a)
{
}

const char *
sp_artist_name(sp_artist *a)
{
    return a->name;
}

bool
sp_artist_is_loaded(sp_artist *a)
{
    return a->loaded;
}

void
sp_artist_release(sp_artist *a)
{
}
