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

DEFINE_READER(user, canonical_name, const char *);
DEFINE_READER(user, display_name, const char *);
DEFINE_READER(user, full_name, const char *);
DEFINE_READER(user, picture, const char *);
DEFINE_READER(user, is_loaded, bool);
DEFINE_SESSION_READER(user, relation_type, sp_relation_type);
