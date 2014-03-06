#include "define.h"
#include "post_api_comm.h"
#include "post_api_login.h"
#include "post_api_upload.h"

#include "getopt.h"

#pragma comment(lib, "ws2_32.lib")

//char IPAddress[] = "127.0.0.1";
//u_short Port = 80;
char IPAddress[] = "218.193.154.30";
u_short Port = 8888;
char SendBuffer[FILE_MAX_BUF];

/*
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
*/

int main(int argc, char * argv[]){
	int Optind = 1;
	int Optchar;

	post_api_login(IPAddress, Port, SendBuffer, "test", "test");
	system("pause");

	while((Optchar = getopt (argc, argv,  "a:u", Optind)) != -1){

		switch(Optchar){
		case 'a':
			post_api_upload(IPAddress, Port, SendBuffer, Optchar, argv[Optind + 1], argv[Optind + 2]);
			break;
		case 'u':
			post_api_upload(IPAddress, Port, SendBuffer, Optchar, argv[Optind + 1], argv[Optind + 2]);
			break;
		default:
			printf("h\n");
			break;
		}
	}
	return 0;
}