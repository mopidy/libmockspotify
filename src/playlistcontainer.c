#include "libmockspotify.h"

sp_playlistcontainer *
mocksp_playlistcontainer_create(void)
{
  return ALLOC(sp_playlistcontainer);
}

DEFINE_REFCOUNTERS_FOR(playlistcontainer);

DEFINE_READER(int, playlistcontainer, num_playlists);
