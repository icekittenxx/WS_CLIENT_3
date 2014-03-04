#ifndef __POST_API_COMM__
#define __POST_API_COMM__

#include "define.h"
#include "http_request.h"
#include "http_response.h"

int post_api_comm(const char *IpAddress, u_short Port, char *SendBuffer);
int post_api_comm_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer);

#endif // __POST_API_COMM__