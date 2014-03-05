#include "http_request.h"

/*
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
*/

using uma::bson::Object;
using uma::bson::ODMObject;
using uma::bson::Document;
using uma::bson::Array;
using uma::bson::String;
using uma::bson::Integer;

int construct_http(const char *IpAddress, u_short Port, int PostAction, char *SendBuffer, char *UserName, char *Password, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE){
	char HttpHeader[SOCKET_MAX_BUF];
	int HttpHeaderLen = 0, HttpContentLen = 0;

	memset(SendBuffer, 0x00, sizeof SendBuffer);
	memset(HttpHeader, 0x00, sizeof HttpHeader);

	HttpContentLen = construct_http_content(PostAction, SendBuffer, UserName, Password, FilePath, FilePathAndFileName, UPLOAD_TYPE);
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
	case POST_API_ACTION_LOGIN:
		strcat(HttpHeader, "POST /api/login");
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

int construct_http_content(int PostAction, char *SendBuffer, char *UserName, char *Password, char *FilePath, char *FilePathAndFileName, int UPLOAD_TYPE){
	char DEVID[MARK_MAX_BUF], SIG[MARK_MAX_BUF];
	//char VER_STRING[MARK_MAX_BUF], SOURCE_STRING[MARK_MAX_BUF], NONCE_STRING[MARK_MAX_BUF], ACTION_STRING[MARK_MAX_BUF];
	int VER, SOURCE, NONCE, ACTION;
	char SECRETKEY[MARK_MAX_BUF];

	memset(DEVID, 0x00, sizeof DEVID);
	memset(SIG, 0x00, sizeof SIG);
	memset(SECRETKEY, 0x00, sizeof SECRETKEY);

	sprintf(DEVID, "%s", "550e8400-e29b-41d4-a716-446655440000");
	VER = 6;
	SOURCE = 21;
	ACTION = PostAction;
	NONCE = get_nonce();
	sprintf(SECRETKEY, "%s", "8YRIJ41NK9PLOT6");

	get_sig(SIG, DEVID, VER, SOURCE, ACTION, NONCE, SECRETKEY);

	using std::string;
	using std::ostringstream;
	
	uma::bson::Document HttpContent;
	uma::bson::Document BsonEmailData;

	HttpContent.set("devid", (string)DEVID);
	HttpContent.set("ver", VER);
	HttpContent.set("source", SOURCE);
	HttpContent.set("action", ACTION);
	HttpContent.set("nonce", NONCE);
	HttpContent.set("sig", (string)SIG);

	switch(PostAction){
	case POST_API_ACTION_INIT:
		HttpContent.set("username", (string)UserName);
		HttpContent.set("password", (string)Password);
		break;
	case POST_API_ACTION_UPLOAD:
		construct_http_content_upload(SendBuffer, FilePathAndFileName);

		BsonEmailData.set("folder", (string)FilePath);
		BsonEmailData.set("content", (string)SendBuffer);
		HttpContent.set("data", BsonEmailData);
		
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

	ostringstream StreamBuf;
	HttpContent.toBson(StreamBuf);
	string StringBuf;
	StringBuf = StreamBuf.str();
	int BufLen;
	BufLen = StringBuf.size();

	memset(SendBuffer, 0x00, sizeof SendBuffer);
	memcpy(SendBuffer, StringBuf.c_str(), BufLen);

	return BufLen;
}

int construct_http_content_upload(char *SendBuffer, char *FilePathAndFileName){
	FILE *PFile = NULL;
	char InBuffer[SOCKET_MAX_BUF];

	memset(InBuffer, 0x00, sizeof InBuffer);
	
	PFile = fopen(FilePathAndFileName, "r");
	if(PFile == NULL){
		return -1;
	}
	else{
		while(fgets(InBuffer, SOCKET_MAX_BUF, PFile)){
			strcat(SendBuffer, InBuffer);
			return 0;
		}
	}
}

int get_nonce(){
	return 1;
}

int get_sig(char *Sig, char *Devid, int Ver, int Source, int Action, int Nonce, char *SecretKey){
	char VerString[MARK_MAX_BUF], SourceString[MARK_MAX_BUF], NonceString[MARK_MAX_BUF], ActionString[MARK_MAX_BUF];
	char TempString[MARK_MAX_BUF];
	int Len = 0;

	int i = 0;

	memset(TempString, 0x00, sizeof TempString);
	memset(VerString, 0x00, sizeof VerString);
	memset(SourceString, 0x00, sizeof SourceString);
	memset(NonceString, 0x00, sizeof NonceString);
	memset(ActionString, 0x00, sizeof ActionString);

	sprintf(VerString, "%d", Ver);
	sprintf(SourceString, "%d", Source);
	sprintf(ActionString, "%d", Action);
	sprintf(NonceString, "%d", Nonce);

	strcat(TempString, Devid);
	strcat(TempString, VerString);
	strcat(TempString, SourceString);
	strcat(TempString, ActionString);
	strcat(TempString, NonceString);
	strcat(TempString, SecretKey);

	MD5Digest(TempString, strlen(TempString), Sig);
	Len = strlen(Sig);

	return Len;
}

/*
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
	//0:	GUID
	//1:	VER
	//2:	SOURCE
	//3:	ACTION
	//4:	NONCE
	//5:	SIG
	
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
*/