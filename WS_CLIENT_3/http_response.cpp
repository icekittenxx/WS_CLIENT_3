#include "http_response.h"

using uma::bson::Object;
using uma::bson::ODMObject;
using uma::bson::Document;
using uma::bson::Array;
using uma::bson::String;
using uma::bson::Integer;
using uma::bson::ObjectId;

/*
int ParseRecvBuffer(char *RecvBuffer, int PostAction){
	int i = 0;
	for(int i = 116; i < 138; i ++){
		printf("%d : %c\n", i, RecvBuffer[i]);
	}
	char temp[100];
	memset(temp, 0x00, sizeof temp);
	memcpy(temp, RecvBuffer + 116, 22);

	for(int i = 0; i < 22; i ++){
		printf("%c", temp[i]);
	}
	Document HttpContent = Document::fromBytes(RecvBuffer + 116, 22);
	using std::string;
	string UID;
	UID = HttpContent.get("hello").getValue<String>().getValue();
	using std::cout;
	cout << UID;
	HttpContent.toJson(cout);
	return 1;
}
*/

int ParseRecvBuffer(char *RecvBuffer, int RecvLen, int PostAction){
	char TempString[FILE_NAME_LEN];
	int BufferLen;
	int ContentStartPos = -1;

	int i = 0;
	
	BufferLen = RecvLen;
	for(i = 0; i < BufferLen; i ++){
		if(i + 8 < BufferLen){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 8);
			if(strcmp(TempString, "\r\n\r\n:") == 0){
				ContentStartPos = i + 9;
				break;
			}
		}
	}

	if(ContentStartPos == -1){
		return -1;
	}
	else{
		using std::string;

		if(PostAction == POST_API_ACTION_LOGIN){
			Document HttpContent = Document::fromBytes(RecvBuffer + ContentStartPos, BufferLen - ContentStartPos);
			char UID[20];
			HttpContent.get("uid").getValue<ObjectId>().getBytes(UID, 12);
		}

		Document HttpContent = Document::fromBytes(RecvBuffer + ContentStartPos, BufferLen - ContentStartPos);
		int error;
		error = HttpContent.get("error").getValue<Integer>().getValue();
		printf("%d\n", error);

		return 0;
	}
}
/**/

/*
int ParseRecvBuffer(char *RecvBuffer, int PostAction){

	char ResponseContentAction[SOCKET_MAX_BUF];
	char ResponseContentError[SOCKET_MAX_BUF];
	char ResponseContentErrormsg[SOCKET_MAX_BUF];
	char ResponseContentAck[SOCKET_MAX_BUF];
	char ResPonseContentCmd[SOCKET_MAX_BUF];
	char ResPonseContentData[SOCKET_MAX_BUF];
	
	char TempString[FILE_NAME_LEN];

	int ContentLength = 0;
	int ContentStartPos = -1;
	int i = 0, j = 0;
	int TempCount = 0;
	int Len = 0;

	memset(ResponseContentAction, 0x00, sizeof ResponseContentAction);
	memset(ResponseContentError, 0x00, sizeof ResponseContentError);
	memset(ResponseContentErrormsg, 0x00, sizeof ResponseContentErrormsg);
	memset(ResponseContentAck, 0x00, sizeof ResponseContentAck);
	memset(ResPonseContentCmd, 0x00, sizeof ResPonseContentCmd);
	memset(ResPonseContentData, 0x00, sizeof ResPonseContentData);

	Len = strlen(RecvBuffer);
	for(i = 0; i < Len; i ++){
		if(i + 8 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 8);
			if(strcmp(TempString, "\r\n\r\n:") == 0){
				ContentStartPos = i + 9;
				break;
			}
		}
	}

	if(ContentStartPos == -1){
		return -1;
	}

	for(i = ContentStartPos; i < Len; i ++){
		if(i + 7 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 7);
			if(strcmp(TempString, "action:") == 0){
				i = i + 8;
				j = 0;
				while(RecvBuffer[i] != ','){
					ResponseContentAction[j] = RecvBuffer[i];
					j ++;
					i ++;
				}
			}
		}

		if(i + 6 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 6);
			if(strcmp(TempString, "error:") == 0){
				i = i + 7;
				j = 0;
				while(RecvBuffer[i] != ','){
					ResponseContentError[j] = RecvBuffer[i];
					j ++;
					i ++;
				}
			}
		}

		if(i + 9 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 9);
			if(strcmp(TempString, "errormsg:") == 0){
				i = i + 10;
				j = 0;
				while(RecvBuffer[i] != ','){
					ResponseContentErrormsg[j] = RecvBuffer[i];
					j ++;
					i ++;
				}
			}
		}

		if(i + 4 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 4);
			if(strcmp(TempString, "ack:") == 0){
				i = i + 5;
				j = 0;
				while(RecvBuffer[i - 1] != ']'){
					ResponseContentAck[j] = RecvBuffer[i];
					j ++;
					i ++;
				}
				i --;
			}
		}

		if(i + 4 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 4);
			if(strcmp(TempString, "cmd:") == 0){
				i = i + 5;
				j = 0;
				TempCount = 0;
				while((RecvBuffer[i - 1] != ']' && TempCount == 0)){
					ResPonseContentCmd[j] = RecvBuffer[i];
					if(RecvBuffer[i] == '['){
						TempCount ++;
					}
					if(RecvBuffer[i] == ']'){
						TempCount --;
					}
					j ++;
					i ++;
				}
				i --;
			}
		}

		if(i + 5 < Len){
			memset(TempString, 0x00, sizeof TempString);
			memcpy(TempString, RecvBuffer + i, 5);
			if(strcmp(TempString, "data:") == 0){
				i = i + 6;
				j = 0;
				while(RecvBuffer[i] != ','){
					ResPonseContentData[j] = RecvBuffer[i];
					j ++;
					i ++;
				}
			}
		}
	}

	return 1;
}
*/