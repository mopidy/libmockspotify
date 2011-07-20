#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_album *
mocksp_album_create(const char *name, sp_artist *artist, int year, const byte *cover,
                    sp_albumtype type, bool loaded, bool available)
{
    sp_album *a = ALLOC(sp_album);

    strcpy(a->name, name);
    a->artist = artist;
    a->year = year;
    memcpy(a->cover, cover, 20);
    a->type = type;
    a->loaded = loaded;
    a->available = available;
    return a;
}

/*** Spotify API ***/

void
sp_album_add_ref(sp_album *a)
{
}

void
sp_album_release(sp_album *a)
{
}

bool
sp_album_is_loaded(sp_album *a)
{
    return a->loaded;
}

bool
sp_album_is_available(sp_album *a)
{
    return a->available;
}

sp_artist *
sp_album_artist(sp_album *a)
{
    return a->artist;
}

const byte *
sp_album_cover(sp_album *a)
{
    return a->cover;
}

const char *
sp_album_name(sp_album *a)
{
    return a->name;
}

int
sp_album_year(sp_album *a)
{
    return a->year;
}

sp_albumtype
sp_album_type(sp_album *a)
{
    return a->type;
}
