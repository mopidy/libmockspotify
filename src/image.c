#include <stdio.h>
#include "libmockspotify.h"

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

DEFINE_REFCOUNTERS_FOR(image);

DEFINE_READER(image, error, sp_error);
DEFINE_READER(image, format, sp_imageformat);
DEFINE_READER(image, image_id, const byte *);

const void *
sp_image_data(sp_image *image, size_t *size)
{
  *size = image->data_size;
  return image->data;
}

bool
sp_image_is_loaded(sp_image *i)
{
  return sp_image_error(i) == SP_ERROR_OK;
}

sp_image*
sp_image_create_from_link(sp_session *session, sp_link *link)
{
  return (sp_image *)registry_find(link->data);
}


sp_image *
sp_image_create(sp_session *session, const byte image_id[20])
{
  sp_link *tmp_link;
  sp_image *tmp_image = ALLOC(sp_image);

  MEMCPY_N(tmp_image->image_id, image_id, byte, 20);
  tmp_link = sp_link_create_from_image(tmp_image);

  return (sp_image *)registry_find(tmp_link->data);
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
