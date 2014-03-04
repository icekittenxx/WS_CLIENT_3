#ifndef __POST_API_INIT__
#define __POST_API_INIT__

#include "define.h"
#include "http_request.h"
#include "http_response.h"

int post_api_init(const char *IpAddress, u_short Port, char *SendBuffer);
int post_api_init_connect(const char *IpAddress, u_short Port, char *SendBuffer);
int post_api_init_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer);

#endif // __POST_API_INIT__