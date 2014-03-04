#ifndef __POST_API_UPLOAD__
#define __POST_API_UPLOAD__

#include "define.h"
#include "http_request.h"
#include "http_response.h"

const char SendEmlFileName[] = "\\sendeml.txt";
const char EmlPath[] = "\\eml\\";
const char EmlSuffix[] = "*.eml";
const char BakFile[] = "copy.txt";

int post_api_upload(const char *IpAddress, u_short Port, char *SendBuffer);
int post_api_upload_connect(const char *IpAddress, u_short Port, char *SendBuffer, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE);
int post_api_upload_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE);

int get_current_path(char *CurrentPath);
int get_find_file_class(char *CurrentPath, char *FindFileClass);

int load_already_send_eml(char *Path, char SendEml[][FILE_NAME_LEN]);
int find_in_send_eml(char *FileName, char SendEml[][FILE_NAME_LEN], int SendEmlNum);

int StringCmp(const void *a, const void *b);

#endif // __POST_API_UPLOAD__