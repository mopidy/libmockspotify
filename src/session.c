#include "libmockspotify.h"

DEFINE_READER(session, connectionstate, sp_connectionstate);
DEFINE_READER(session, userdata, void *);

const char * sp_build_id(void)
{
  return "9.1.32.g8edbd53c Release (Core: 0.5.3.425.g18537e22)";
}

sp_playlistcontainer *
sp_session_playlistcontainer(sp_session *session)
{
  return mocksp_playlistcontainer_create();
}

sp_error
sp_session_create(const sp_session_config *config, sp_session * *sess)
{
  if (memcmp(config->application_key, "appkey_good", config->application_key_size))
      return SP_ERROR_BAD_APPLICATION_KEY;

  *sess = ALLOC(sp_session);
  sp_session *session = *sess;

  session->config.api_version       = config->api_version;
  session->config.cache_location    = strclone(config->cache_location);
  session->config.settings_location = strclone(config->settings_location);
  session->config.user_agent        = strclone(config->user_agent);
  session->config.callbacks         = ALLOC(sp_session_callbacks);
  session->config.userdata          = config->userdata;

  session->config.application_key   = ALLOC_N(byte, config->application_key_size);
  memcpy((char *) session->config.application_key, config->application_key, config->application_key_size);
  MEMCPY((sp_session_callbacks *) session->config.callbacks, config->callbacks, sp_session_callbacks);

  // TODO: v0.0.8 (and earlier) directly call `notify_main_thread` callback here, before returning
  if (config->callbacks->notify_main_thread)
    config->callbacks->notify_main_thread(NULL);

  return SP_ERROR_OK;
}

void sp_session_release(sp_session *session)
{
}

void
sp_session_process_events(sp_session *session, int *next_timeout)
{
  *next_timeout = 1;
}

void
sp_session_login(sp_session *session, const char *username, const char *password, bool remember_me)
{
  session->connectionstate = SP_CONNECTION_STATE_LOGGED_IN;

  if (remember_me)
  {
    session->username = strclone(username);
  }
}

void
sp_session_logout(sp_session *session)
{
  session->connectionstate = SP_CONNECTION_STATE_LOGGED_OUT;
}

sp_user *
sp_session_user(sp_session *session)
{
  return mocksp_user_create(NULL, NULL, NULL, NULL, SP_RELATION_TYPE_NONE, true);
}
