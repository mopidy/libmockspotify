/*
 * API for libmockspotify
 *
 */

#ifndef LIBMOCKSPOTIFY_API_H
#define LIBMOCKSPOTIFY_API_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libspotify/api.h"
#include "util.h"

struct sp_session
{
  char *username;
  sp_session_config config;
  void *userdata;
  sp_connectionstate connectionstate;
  size_t cache_size;

  int num_friends;
  sp_user **friends;
};

struct sp_album
{
  char *name;
  sp_artist *artist;
  int year;
  byte cover[20];
  int type;
  bool is_loaded;
  bool is_available;
};

struct sp_albumbrowse
{
  sp_error error;
  sp_album *album;
  sp_artist *artist;

  int num_copyrights;
  char **copyrights;

  int num_tracks;
  sp_track **tracks;

  char *review;

  albumbrowse_complete_cb *callback;
  void *userdata;
};

struct sp_artist
{
  char *name;
  int is_loaded;
};

struct sp_artistbrowse
{
  sp_error error;
  sp_artist *artist;
  int num_portraits;
  byte **portraits;
  int num_tracks;
  sp_track **tracks;
  int num_albums;
  sp_album **albums;
  int num_similar_artists;
  sp_artist **similar_artists;
  char *biography;

  artistbrowse_complete_cb *callback;
  void *userdata;
};

struct sp_image
{
  byte image_id[20];
  sp_imageformat format;
  size_t data_size;
  byte *data;
  sp_error error;
};

struct sp_playlist
{
  char *name;
  sp_track *track[32];
  int num_tracks;
  sp_playlist_callbacks *callbacks;
  void *userdata;
  bool is_loaded;
  bool is_collaborative;
};

struct sp_playlistcontainer
{
  sp_playlist *playlist[32];
  int num_playlists;
  sp_playlistcontainer_callbacks *callbacks;
  void *userdata;
};

struct sp_search
{
  int total_tracks;
  int num_tracks;
  int num_artists;
  int num_albums;
  sp_track *track[20];
  sp_album *album[20];
  sp_artist *artist[20];
  char *query;
  char *did_you_mean;
  int error;
  bool is_loaded;
};

struct sp_track
{
  char *name;
  int num_artists;
  sp_artist **artists;
  sp_album *album;
  int duration;
  int popularity;
  int disc;
  int index;
  sp_error error;

  bool is_loaded;
  bool is_starred;
  bool is_local;
  bool is_autolinked;
  bool is_available;
};

struct sp_user
{
  char *canonical_name;
  char *display_name;
  char *full_name;
  char *picture;
  sp_relation_type relation_type;
  bool is_loaded;
};

struct sp_link
{
  char *data;
};

struct sp_toplistbrowse
{
  sp_error error;

  int num_artists;
  sp_artist **artists;

  int num_albums;
  sp_album **albums;

  int num_tracks;
  sp_track **tracks;

  toplistbrowse_complete_cb *callback;
  void *userdata;
};

void *
registry_find(const char *url);

void
registry_add(const char *url, void *ptr);

sp_session *
mocksp_session_create(const sp_session_config *, int, sp_user **);

sp_album *
mocksp_album_create(const char *, sp_artist *, int, const byte *, sp_albumtype, bool, bool);

sp_albumbrowse *
mocksp_albumbrowse_create(sp_error, sp_album *, sp_artist *, int, const char **, int, sp_track **, const char *, albumbrowse_complete_cb *cb, void *userdata);

sp_artist *
mocksp_artist_create(const char *, bool);

sp_artistbrowse *
mocksp_artistbrowse_create(sp_error, sp_artist *, int, const byte **, int, sp_track **, int, sp_album **, int, sp_artist **, const char *, artistbrowse_complete_cb *, void *);

sp_playlist *
mocksp_playlist_create(const char *);

sp_playlistcontainer *
mocksp_playlistcontainer_create(void);

sp_track *
mocksp_track_create(const char *, int, sp_artist **, sp_album *, int, int, int, int, sp_error, bool, bool, bool, bool, bool);

sp_user *
mocksp_user_create(const char *, const char *, const char *, const char *, sp_relation_type, bool); 

sp_image*
mocksp_image_create(const byte[20], sp_imageformat, size_t, const byte *, sp_error);


sp_toplistbrowse *
mocksp_toplistbrowse_create(sp_error, int, sp_artist **, int, sp_album **, int, sp_track **, toplistbrowse_complete_cb *, void *);

#endif /* LIBMOCKSPOTIFY_API_H */
