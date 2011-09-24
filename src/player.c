#include "libmockspotify.h"

sp_error
sp_session_player_load(sp_session *session, sp_track *track)
{
  session->player.track = track;
  return SP_ERROR_OK;
}

void
sp_session_player_seek(sp_session *session, int offset)
{
  session->player.position = offset;
}

void
sp_session_player_play(sp_session *session, bool play)
{
  session->player.playing = play;
}

void
sp_session_player_unload(sp_session *session)
{
  session->player.track = NULL;
}

sp_error
sp_session_player_prefetch(sp_session *session, sp_track *track)
{
  return SP_ERROR_OK;
}
