#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libmockspotify.h"
#include "util.h"

/*** Spotify API ***/
void
sp_link_add_ref(sp_link *link)
{
}

void
sp_link_release(sp_link *link)
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
  strncpy(lnk->data, link, 1024);
  return lnk;
}

sp_link *
sp_link_create_from_user(sp_user *user)
{
  sp_link *link = ALLOC(sp_link);
  sprintf(link->data, "spotify:user:%s", user->canonical_name);
  return link;
}

sp_link *
sp_link_create_from_image(sp_image *image)
{
  sp_link *link = ALLOC(sp_link);
  sprintf(link->data, "spotify:image:");
  atohex(link->data + strlen("spotify:image:"), image->image_id, 40);
  return link;
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

sp_artist *
sp_link_as_artist(sp_link *link)
{
    if (strncmp(link->data, "spotify:artist:", strlen("spotify:artist:")))
        return NULL;
    return mocksp_artist_create(link->data + strlen("spotify:artist:"), 1);
}

sp_album *
sp_link_as_album(sp_link *link)
{
    if (strncmp(link->data, "spotify:album:", strlen("spotify:album:")))
        return NULL;
    return mocksp_album_create(link->data + strlen("spotify:album:"),
                       mocksp_artist_create("mock", 1), 1901, (byte *) "",
                       SP_ALBUMTYPE_ALBUM, 1, 1);
}

sp_link *
sp_link_create_from_track(sp_track *track, int offset)
{
    sp_link *l = malloc(sizeof(sp_link));

    memset(l, 0, sizeof(sp_link));
    sprintf(l->data, "spotify:track:%s/%d", track->name, offset);
    return l;
}

sp_link *
sp_link_create_from_album(sp_album *album)
{
    sp_link *l = malloc(sizeof(sp_link));

    memset(l, 0, sizeof(sp_link));
    sprintf(l->data, "spotify:album:%s", album->name);
    return l;
}

sp_link *
sp_link_create_from_playlist(sp_playlist *playlist)
{
    sp_link *l = malloc(sizeof(sp_link));

    memset(l, 0, sizeof(sp_link));
    sprintf(l->data, "spotify:playlist:%s", playlist->name);
    return l;
}

sp_link *
sp_link_create_from_artist(sp_artist *artist)
{
    sp_link *l = malloc(sizeof(sp_link));

    memset(l, 0, sizeof(sp_link));
    sprintf(l->data, "spotify:artist:%s", artist->name);
    return l;
}

sp_link *
sp_link_create_from_search(sp_search *s)
{
    sp_link *l = malloc(sizeof(sp_link));

    memset(l, 0, sizeof(sp_link));
    sprintf(l->data, "spotify:search:%s", s->query);
    return l;
}

sp_track *
sp_link_as_track(sp_link *link)
{
  return mocksp_track_create("Bogus", 0, NULL, NULL, 100, 42, 1, 7, SP_ERROR_OK, 1);
}

sp_track *
sp_link_as_track_and_offset(sp_link *link, int *offset)
{
  /* parse the offset */
  int mins = 0, secs = 0;
  char *optr = NULL;

  if (optr = strchr(link->data, '#'))
  {
    sscanf(optr, "#%u:%u", &mins, &secs);
    *offset = (mins * 60 + secs) * 1000;
  }
  else
  {
    *offset = 0;
  }

  return sp_link_as_track(link);
}
