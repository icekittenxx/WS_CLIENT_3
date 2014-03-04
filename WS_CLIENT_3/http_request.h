#ifndef __HTTP_REQUEST__
#define __HTTP_REQUEST__

#include "define.h"
#include "bson_parser.h"

int construct_http(const char *IpAddress, u_short Port, int PostAction, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE);
int construct_http_header(const char *IpAddress, u_short Port, int PostAction, char *HttpHeader, int HttpContentLen);
int construct_http_content(int PostAction, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE);
int construct_http_content_header(int PostAction, char *HttpContentHeader);

#endif // __HTTP_REQUEST__