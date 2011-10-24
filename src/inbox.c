#include "libmockspotify.h"

sp_inbox *
sp_inbox_post_tracks(sp_session *session, const char *user, sp_track *const *tracks, int num_tracks, const char *message, inboxpost_complete_cb *callback, void *userdata)
{
  if (num_tracks > 0)
  {
    sp_inbox *inbox = ALLOC(sp_inbox);

    inbox->user     = strclone(user);
    inbox->message  = strclone(message);
    inbox->callback = callback;
    inbox->userdata = userdata;

    inbox->tracks = ALLOC_N(sp_track, num_tracks);
    inbox->num_tracks = num_tracks;
    MEMCPY_N(inbox->tracks, tracks, sp_track *, num_tracks);

    return inbox;
  }
}

DEFINE_REFCOUNTERS_FOR(inbox);

sp_error
sp_inbox_error(sp_inbox *inbox)
{
  return SP_ERROR_OK;
}
