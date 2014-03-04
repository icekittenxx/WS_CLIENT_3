#include "post_api_login.h"

int post_api_login(const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password){

	post_api_login_connect(IpAddress, Port, SendBuffer, UserName, Password);

	return 0;
}

int post_api_login_connect(const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password){
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

	Ret = post_api_login_communcation(ClientSocket, IpAddress, Port, SendBuffer, UserName, Password);
	if(Ret == -1){
		return -1;
	}

	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}

int post_api_login_communcation(SOCKET ClientSocket, const char *IpAddress, u_short Port, char *SendBuffer, char *UserName, char *Password){
	//char *SendBuffer, *RecvBuffer;
	char RecvBuffer[SOCKET_MAX_BUF];
	int SendRes = 0, RecvRes = 0;
	int SendLen = 0, RecvLen = 0;
	int RecvBufferIsEmpty = 0;
	int ParseRes = 0;

	construct_http(IpAddress, Port, POST_API_ACTION_INIT, SendBuffer, UserName, Password, NULL, NULL, NULL);

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
			ParseRes = ParseRecvBuffer(RecvBuffer, POST_API_ACTION_LOGIN);
			if(ParseRes != -1){
				//undo
			}
		}
	}

	//undo
	return 1; 
}