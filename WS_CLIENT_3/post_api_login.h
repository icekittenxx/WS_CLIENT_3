#ifndef __POST_API_INIT__
#define __POST_API_INIT__

#include "define.h"
#include "http_request.h"
#include "http_response.h"

int post_api_login(const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password);
int post_api_login_connect(const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password);
int post_api_login_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password);

#endif // __POST_API_INIT__