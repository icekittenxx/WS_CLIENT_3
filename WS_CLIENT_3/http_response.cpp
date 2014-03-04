#include "http_response.h"

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