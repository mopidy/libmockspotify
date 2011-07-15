#include <stdlib.h>
#include <string.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/

sp_user *
mocksp_user_create(char *canonical_name, char *display_name, char *full_name,
                   char *picture, sp_relation_type relation, bool loaded)
{
    sp_user *user;

    user = malloc(sizeof(sp_user));
    user->canonical_name = canonical_name;
    user->display_name = display_name;
    user->full_name = full_name;
    user->picture = picture;
    user->relation = relation;
    user->loaded = loaded;

    return user;
}

/*** Spotify API ***/

void
sp_user_add_ref(sp_user *user)
{
}

void
sp_user_release(sp_user *user)
{
}

bool
sp_user_is_loaded(sp_user *user)
{
    return user->loaded;
}

const char *
sp_user_canonical_name(sp_user *user)
{
    return user->canonical_name;
}

const char *
sp_user_display_name(sp_user *user)
{
    return user->display_name;
}

const char *
sp_user_full_name(sp_user *user)
{
    return user->loaded ? user->full_name : NULL;
}

const char *
sp_user_picture(sp_user *user)
{
    return user->loaded ? user->picture : NULL;
}

sp_relation_type
sp_user_relation_type(sp_session *session, sp_user *user)
{
    return user->relation;
}