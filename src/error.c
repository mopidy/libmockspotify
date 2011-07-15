#include <stdio.h>
#include <stdlib.h>
#include "libmockspotify.h"

/*** MockSpotify API ***/
const char*
sp_error_message(sp_error error)
{
    char *buff = malloc(20 * sizeof(char));
    sprintf(buff, "sp_error: %d", error);
    return buff;
}
