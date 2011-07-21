#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

mocking_data g_data;

event_type eventq[16];
int events = 0;

/*** Spotify API ***/

void
sp_session_login(sp_session *session, const char *username,
                 const char *password)
{
    strcpy(g_data.username, username);
    strcpy(g_data.password, password);
    eventq[events++] = MOCK_LOGGED_IN;
}

void
sp_session_logout(sp_session *session)
{
    eventq[events++] = MOCK_LOGGED_OUT;
}

sp_user *
sp_session_user(sp_session *session)
{
    return mocksp_user_create(g_data.username, "", NULL, "", 0, 1);
}

sp_playlistcontainer *
sp_session_playlistcontainer(sp_session *session)
{
    return mocksp_playlistcontainer_create();
}

sp_error
sp_session_create(const sp_session_config *config, sp_session **sess)
{
    if (memcmp
        (config->application_key, "appkey_good", config->application_key_size))
        return SP_ERROR_BAD_APPLICATION_KEY;
    g_data.config.cache_location = malloc(strlen(config->cache_location) + 1);
    g_data.config.settings_location =
        malloc(strlen(config->settings_location) + 1);
    g_data.config.application_key = malloc(config->application_key_size);
    g_data.config.user_agent = malloc(strlen(config->user_agent) + 1);
    g_data.config.callbacks =
        (sp_session_callbacks *) malloc(sizeof(sp_session_callbacks));
    g_data.config.userdata = config->userdata;

    g_data.config.api_version = config->api_version;
    strcpy((char *)g_data.config.cache_location, config->cache_location);
    strcpy((char *)g_data.config.settings_location, config->settings_location);
    memcpy((char *)g_data.config.application_key, config->application_key,
           config->application_key_size);
    strcpy((char *)g_data.config.user_agent, config->user_agent);
    memcpy((char *)g_data.config.callbacks, config->callbacks,
           sizeof(sp_session_callbacks));
    g_data.config.userdata = config->userdata;
    return SP_ERROR_OK;
}

void *
sp_session_userdata(sp_session *session)
{
    return g_data.config.userdata;
}

void
sp_session_preferred_bitrate(sp_session *s, sp_bitrate b)
{
    // TODO
}

void
sp_session_process_events(sp_session *session, int *next_timeout)
{
    if (events > 0) {
        events--;
        event_type next = eventq[events];

        if (next == MOCK_LOGGED_IN) {
            g_data.config.callbacks->logged_in(session, SP_ERROR_OK);
        }
    }
    *next_timeout = 1;
}

sp_playlist *
sp_session_starred_create(sp_session *session)
{
    return mocksp_playlist_create("Starred");
}

sp_error
sp_session_player_load(sp_session *session, sp_track *track)
{
    return 0;
}

void
sp_session_player_seek(sp_session *session, int offset)
{
}

void
sp_session_player_play(sp_session *session, bool b)
{
}

void
sp_session_player_unload(sp_session *session)
{
}
