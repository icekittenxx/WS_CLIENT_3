#include "define.h"
#include "post_api_comm.h"
#include "post_api_login.h"
#include "post_api_upload.h"

#pragma comment(lib, "ws2_32.lib")

char IPAddress[] = "127.0.0.1";
u_short Port = 80;
char SendBuffer[FILE_MAX_BUF];

int main(){
	int CommandId = 0;

	post_api_login(IPAddress, Port, SendBuffer, "test", "test");

	while(~scanf("%d", &CommandId)){
		printf("the program is running");

		if(CommandId == 1){
			post_api_upload(IPAddress, Port, SendBuffer);
		}
		else{
			post_api_comm(IPAddress, Port, SendBuffer);
		}
	}

	return 0;
}