#include <stdio.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

/*** Spotify API ***/

void
sp_image_add_ref(sp_image *image)
{
}

void
sp_image_release(sp_image *image)
{
}

bool
sp_image_is_loaded(sp_image *i)
{
    /* TODO */
    return 1;
}

sp_imageformat
sp_image_format(sp_image *i)
{
    /* TODO */
    return 1;
}

sp_error
sp_image_error(sp_image *i)
{
    /* TODO */
    return 0;
}

const void *
sp_image_data(sp_image *i, size_t *t)
{
    /* TODO */
    return NULL;
}

sp_image *
sp_image_create(sp_session *session, const byte image_id[20])
{
    /* TODO */
    return NULL;
}

void
sp_image_add_load_callback(sp_image *i, image_loaded_cb *callback,
                           void *userdata)
{
    /* TODO */
}

void
sp_image_remove_load_callback(sp_image *i, image_loaded_cb *callback,
                              void *userdata)
{
    /* TODO */
}
