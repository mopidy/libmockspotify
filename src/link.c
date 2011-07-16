#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** Spotify API ***/
sp_link *
sp_link_create_from_string(const char *link)
{
  /* unless the link starts with spotify: it is invalid */
  if ( ! STARTS_WITH(link, "spotify:"))
  {
    return NULL;
  }

  sp_link *lnk = ALLOC(sp_link);
  snprintf(lnk->data, 1024 /* max size of data in sp_link */, "%s", link);
  return lnk;
}

int
sp_link_as_string(sp_link *link, char *buffer, int buffer_size)
{
  strncpy(buffer, link->data, buffer_size);

  if (buffer_size > 0)
  {
    buffer[buffer_size - 1] = '\0';
  }

  return strlen(link->data);
}
