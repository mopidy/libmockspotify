#include "libmockspotify.h"

sp_user *
mocksp_user_create(const char *canonical_name, const char *display_name, const char *full_name,
                   const char *picture, sp_relation_type relation, bool is_loaded)
{
    sp_user *user = ALLOC(sp_user);

    user->canonical_name = strclone(canonical_name);
    user->display_name   = strclone(display_name);
    user->full_name      = strclone(full_name);
    user->picture        = strclone(picture);
    user->relation_type  = relation;
    user->is_loaded      = is_loaded;

    return user;
}

DEFINE_REFCOUNTERS_FOR(user);

DEFINE_READER(const char *, user, canonical_name);
DEFINE_READER(const char *, user, display_name);
DEFINE_READER(const char *, user, full_name);
DEFINE_READER(const char *, user, picture);
DEFINE_READER(bool, user, is_loaded);
DEFINE_SESSION_READER(sp_relation_type, user, relation_type);
