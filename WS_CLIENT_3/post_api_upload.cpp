#include "post_api_upload.h"

int post_api_upload(const char *IpAddress, u_short Port, char *SendBuffer){
	FILE *PP;
	struct _finddata_t FindFile;
	long FHandle;

	char CurrentPath[FILE_NAME_LEN];
	int CurrentPathLen = 0;
	char SendEml[EML_MAX_NUM][FILE_NAME_LEN];
	int SendEmlNum;
	char FindFileClass[FILE_NAME_LEN];
	int FindFileClassLen = 0;
	char FileName[FILE_NAME_LEN];
	char FilePathName[FILE_NAME_LEN];
	int Res = 0;
	
	memset(CurrentPath, 0x00, sizeof CurrentPath);
	memset(SendEml, 0x00, sizeof SendEml);
	memset(FindFileClass, 0x00, sizeof FindFileClass);

	CurrentPathLen = get_current_path(CurrentPath);

	SendEmlNum = load_already_send_eml(CurrentPath, SendEml);

	FindFileClassLen = get_find_file_class(CurrentPath, FindFileClass);

	PP = fopen(BakFile, "w");
	fclose(PP);

	if((FHandle = _findfirst(FindFileClass, &FindFile)) == -1L){
	}
	else{
		do{

			PP = fopen(BakFile, "a+");
			memset(FileName, 0x00, sizeof FileName);
			strcpy(FileName, FindFile.name);
			fprintf(PP, "%s\n", FileName);
			fclose(PP);

			Res = find_in_send_eml(FindFile.name, SendEml, SendEmlNum);
			if(Res == 1){
				continue;
			}

			memset(FilePathName, 0x00, sizeof FilePathName);
			strcat(FilePathName, CurrentPath);
			strcat(FilePathName, EmlPath);
			strcat(FilePathName, FindFile.name);

			Res = post_api_upload_connect(IpAddress, Port, SendBuffer, FilePathName, UPLOAD_TYPE_EMAIL);
		}while(_findnext(FHandle, &FindFile) == 0);
		_findclose(FHandle);
	}

	return 0;
}

int post_api_upload_connect(const char *IpAddress, u_short Port, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE){
	WSADATA  Ws;
	SOCKET ClientSocket;
	HANDLE hThread = NULL;
	struct sockaddr_in ServerAddr;
	int AddrLen = 0;
	int Ret = 0;
	
	if(WSAStartup(MAKEWORD(2, 2), &Ws) != 0){
		return -1;
	}

	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(ClientSocket == INVALID_SOCKET){
		return -1;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(IpAddress);
	ServerAddr.sin_port = htons(Port);
	memset(ServerAddr.sin_zero, 0x00, 8);

	Ret = connect(ClientSocket, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
	if(Ret == SOCKET_ERROR){
		return -1;
	}

	Ret = post_api_upload_communcation(ClientSocket, IpAddress, Port, SendBuffer, FilePathName, UPLOAD_TYPE);
	if(Ret == -1){
		return -1;
	}

	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

int post_api_upload_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer, char *FilePathName, int UPLOAD_TYPE){
	//char *SendBuffer, *RecvBuffer;
	char RecvBuffer[SOCKET_MAX_BUF];
	int SendRes = 0, RecvRes = 0;
	int SendLen = 0, RecvLen = 0;
	int RecvBufferIsEmpty = 0;
	int ParseRes = 0;

	construct_http(IpAddress, Port, POST_API_ACTION_INIT, SendBuffer, FilePathName, UPLOAD_TYPE);

	SendRes = send(ClientSocket, SendBuffer, SendLen, 0);
	if(SendRes == SOCKET_ERROR){
		return -1;
	}

	memset(RecvBuffer, 0x00, sizeof RecvBuffer);

	while(1){
		RecvRes = recv(ClientSocket, RecvBuffer, SOCKET_MAX_BUF, 0);
		if(RecvRes == 0 || RecvRes == SOCKET_ERROR){
			break;
		}

		if((int)strlen(RecvBuffer) != 0){
			RecvBufferIsEmpty = 0;
		}

		if(RecvBufferIsEmpty == 0){
			ParseRes = ParseRecvBuffer(RecvBuffer, POST_API_ACTION_UPLOAD);
			if(ParseRes != -1){
				// undo
			}
		}
	}

	//undo
	return 1; 
}

int get_current_path(char *CurrentPath){
	char *TempString;
	int len = 0;
	TempString = getcwd(NULL, 0);
	strcpy(CurrentPath, TempString);
	free(TempString);
	len = strlen(CurrentPath);
	return len;
}

int get_find_file_class(char *CurrentPath, char *FindFileClass){
	int len = 0;
	strcat(FindFileClass, CurrentPath);
	strcat(FindFileClass, EmlPath);
	strcat(FindFileClass, EmlSuffix);
	len = strlen(FindFileClass);
	return len;
}

int load_already_send_eml(char *Path, char SendEml[][FILE_NAME_LEN]){
	FILE * PFile = NULL;
	char SendEmlName[FILE_NAME_LEN];
	int SendEmlNum = 0;

	int i = 0;

	memset(SendEmlName, 0x00, sizeof SendEmlName);

	strcat(SendEmlName, Path);
	strcat(SendEmlName, SendEmlFileName);

	PFile = fopen(SendEmlName, "r");
	if(PFile == NULL){
		PFile = fopen(SendEmlName, "w");
		fclose(PFile);
	}
	else{
		SendEmlNum = 0;
		while(fgets(SendEml[SendEmlNum], FILE_NAME_LEN, PFile)){
			for(i = 0; i < strlen(SendEml[SendEmlNum]); i ++){
				if(SendEml[SendEmlNum][i] >= 'A' && SendEml[SendEmlNum][i] <= 'Z'){
					SendEml[SendEmlNum][i] = SendEml[SendEmlNum][i] - 'A' + 'a';
				}
			}
			SendEml[SendEmlNum][i - 1] = 0;
			SendEmlNum ++;
		}

		qsort(SendEml, SendEmlNum, sizeof SendEml[0], StringCmp);

	}
	return 0;
}

int find_in_send_eml(char *FileName, char SendEml[][FILE_NAME_LEN], int SendEmlNum){
	char TempString[FILE_NAME_LEN];

	int Res = 0;
	int i = 0;

	memset(TempString, 0x00, sizeof TempString);
	strcpy(TempString, FileName);

	for(i = 0; i < strlen(TempString); i ++){
		if(TempString[i] >= 'A' && TempString[i] <= 'Z'){
			TempString[i] = TempString[i] - 'A' + 'a';
		}
	}

	for(int i = 0; i < SendEmlNum; i ++){
		if(strcmp(SendEml[i], TempString) == 0){
			Res = 1;
			break;
		}
	}

	return Res;
}

int StringCmp(const void *a, const void *b){
	int result = 0;
	result = strcmp((char *)a, (char *)b);
	return result;
}