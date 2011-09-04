#include "libmockspotify.h"

/**
 * TODO:
 *
 * is_loaded
 * error
 * artist
 * num_portraits
 * portrait
 * num_tracks
 * artistbrowse_track
 * num_albums
 * artistbrowse_album
 * num_similar_artists
 * similar_artist
 * biography
 * */
sp_artistbrowse *
mocksp_artistbrowse_create(sp_artist *artist, bool is_loaded)
{
  sp_artistbrowse *artistbrowse = ALLOC(sp_artistbrowse);
  artistbrowse->artist    = artist;
  artistbrowse->is_loaded = is_loaded;
  return artistbrowse;
}

DEFINE_REFCOUNTERS_FOR(artistbrowse);
DEFINE_READER(bool, artistbrowse, is_loaded);
