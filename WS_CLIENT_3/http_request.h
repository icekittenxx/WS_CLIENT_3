#ifndef __HTTP_REQUEST__
#define __HTTP_REQUEST__

#include "define.h"
#include "bson_parser.h"
#include "md5.h"

int construct_http(const char *IpAddress, u_short Port, int PostAction, char *SendBuffer, char *UserName, char *Password, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE);
int construct_http_header(const char *IpAddress, u_short Port, int PostAction, char *HttpHeader, int HttpContentLen);
int construct_http_content(int PostAction, char *SendBuffer, char *UserName, char *Password, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE);
int construct_http_content_upload(char *SendBuffer, char *FilePathAndFileName);
//int construct_http_content_header(int PostAction, char *HttpContentHeader);

int get_nonce();
int get_sig(char *Sig, char *Devid, int Ver, int Source, int Action, int Nonce, char *SecretKey);

#endif // __HTTP_REQUEST__