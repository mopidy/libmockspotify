#include <string.h>
#include "libmockspotify.h"

/*** Spotify API ***/
void
sp_link_add_ref(sp_link * link)
{
}

void
sp_link_release(sp_link * link)
{
}

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

sp_link *
sp_link_create_from_user(sp_user *user)
{
  char *link = ALLOC_N(char, 1024);
  sprintf(link, "spotify:user:%s", user->canonical_name);
  return sp_link_create_from_string(link);
}

sp_link *
sp_link_create_from_image(sp_image *image)
{
}

int
sp_link_as_string(sp_link *link, char *buffer, int buffer_size)
{
  strncpy(buffer, link->data, buffer_size);

  if (buffer_size > 0)
  {
    buffer[buffer_size - 1] = '\0';
  }

  return (int) strlen(link->data);
}

sp_linktype
sp_link_type(sp_link *link)
{
  #define LINK_IS(type) (strstr(link->data, ":" #type))
  #define LINK_CASE_FOR(string, type) if (LINK_IS(string)) { return SP_LINKTYPE_##type; }

  LINK_CASE_FOR(search, SEARCH);
  LINK_CASE_FOR(track,  TRACK);
  LINK_CASE_FOR(album,  ALBUM);
  LINK_CASE_FOR(artist, ARTIST);
  LINK_CASE_FOR(image,  IMAGE);

  // Order of these three is significant
  LINK_CASE_FOR(playlist, PLAYLIST);
  LINK_CASE_FOR(starred,  STARRED);
  LINK_CASE_FOR(user,     PROFILE);

  return SP_LINKTYPE_INVALID;
}

sp_user *
sp_link_as_user(sp_link *link)
{
  return mocksp_user_create(link->data, "", "", "", SP_RELATION_TYPE_UNKNOWN, 1);
}
