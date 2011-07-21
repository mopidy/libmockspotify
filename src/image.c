#include "libmockspotify.h"

/*** MockSpotify API ***/
sp_image*
mocksp_image_create(const byte image_id[20], sp_imageformat format, size_t data_size, const byte *data, sp_error error)
{
  sp_image *image = ALLOC(sp_image);
  memcpy(image->image_id, image_id, 20);
  image->format = format;
  image->data_size = data_size;
  image->data = ALLOC_N(byte, data_size + 1);
  memcpy(image->data, data, data_size);
  image->error = error;
  return image;
}

/*** Spotify API ***/

sp_image*
sp_image_create_from_link(sp_session *session, sp_link *l)
{
  byte *real_id  = l->data + strlen("spotify:image:");
  byte *image_id = ALLOC_N(byte, 20);
  memcpy(image_id, real_id, 20); // TODO: convert "deadbeef" to array of: [0xDE, 0xAD, 0xBE, 0xEF]
  return mocksp_image_create(image_id, SP_IMAGE_FORMAT_JPEG, 0, NULL, SP_ERROR_OK);
}

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
    return sp_image_error(i) == SP_ERROR_OK;
}

sp_imageformat
sp_image_format(sp_image *i)
{
    return i->format;
}

sp_error
sp_image_error(sp_image *i)
{
    return i->error;
}

const void *
sp_image_data(sp_image *i, size_t *t)
{
    *t = i->data_size;
    return i->data;
}

sp_image *
sp_image_create(sp_session *session, const byte image_id[20])
{
    sp_image *image = ALLOC(sp_image);
    memcpy(image->image_id, image_id, 20);
    return image;
}

const byte*
sp_image_image_id(sp_image *i)
{
  return i->image_id;
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
