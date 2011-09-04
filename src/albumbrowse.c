#include "libmockspotify.h"

/* TODO:
 * is_loaded
 * artist
 * error
 * album
 * artist
 * num_copyrights
 * copyright
 * track
 * review
 *
 * callback
 * userdata
 * */
sp_albumbrowse *
mocksp_albumbrowse_create(sp_album *album, bool is_loaded)
{
  sp_albumbrowse *albumbrowse = ALLOC(sp_albumbrowse);

  albumbrowse->is_loaded = is_loaded;
  albumbrowse->album     = album;

  return albumbrowse;
}

DEFINE_REFCOUNTERS_FOR(albumbrowse);
DEFINE_READER(albumbrowse, album, sp_album *);
DEFINE_READER(albumbrowse, is_loaded, bool);

sp_albumbrowse *
sp_albumbrowse_create(sp_session *session, sp_album *album,
                      albumbrowse_complete_cb cb, void *userdata)
{
  return mocksp_albumbrowse_create(album, 1);
}

int
sp_albumbrowse_num_tracks(sp_albumbrowse *x)
{
  return 0;
}
