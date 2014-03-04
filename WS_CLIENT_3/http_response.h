#ifndef __HTTP_REPONSE__
#define __HTTP_REPONSE__

#include "define.h"
#include "bson_parser.h"

int ParseRecvBuffer(char *RecvBuffer, int PostAction);

#endif // __HTTP_REPONSE__