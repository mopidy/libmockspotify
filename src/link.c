#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** Spotify API ***/
sp_link *
sp_link_create_from_string(const char *link)
{
  /* unless the link starts with spotify: it is invalid */
  if (STRNCMP2(link, "spotify:") != 0)
  {
    return NULL;
  }

  sp_link *lnk = ALLOC(sp_link);
  snprintf(lnk->data, 1024 /* max size of data in sp_link */, "%s", link);
  return lnk;
}
