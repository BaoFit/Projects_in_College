#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <math.h>

#define    BUFLEN        2000                  // 缓冲区大小
#define WSVERS        MAKEWORD(2, 0)        // 指明版本2.0 
#pragma comment(lib,"ws2_32.lib")         // 指明winsock 2.0 Llibrary

 /*------------------------------------------------------------------------
  * main - TCP client for DAYTIME service
  *------------------------------------------------------------------------
*/
     
 SOCKET    sock,sockets[100] = {NULL};                          /* socket descriptor            */
char    *packet = NULL;               /* buffer for one line of text    */
char *pts,*input;
HANDLE hThread;
unsigned threadID;
unsigned int __stdcall Chat(PVOID PM ) 
{
	time_t    now;
	(void) time(&now);
	pts = ctime(&now);
	char buf[2000];

	while(1)                //接收端接受信息
	{
		int cc = recv(sock, buf, BUFLEN, 0);   //cc为接收的字符数  
		if(cc == SOCKET_ERROR|| cc == 0)
		{
		//	printf("Error: %d.----",GetLastError());
		//	printf("与服务器断开连接！\n");
			CloseHandle(hThread);
			(void)closesocket(sock);
			break;
		}
		else if(cc > 0) 
		{
			printf("%s\n",buf);
		}     
	}
    return 0;
}
  
int main(int argc, char *argv[])
{
	time_t    now;
	(void) time(&now);
	pts = ctime(&now);
	char *host = "172.22.65.200";        /* server IP to connect         */
	char *service = "5050";          /* server port to connect       */
	struct  sockaddr_in sin;            /* an Internet endpoint address    */
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);       /* 启动某版本Socket的DLL        */        
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((u_short)atoi(service));    //atoi：把ascii转化为int. htons：主机序(host)转化为网络序(network), s--short
	sin.sin_addr.s_addr = inet_addr(host);           //如果host为域名，需要先用函数gethostbyname把域名转化为IP地址
  
	sock = socket(PF_INET, SOCK_STREAM,0);
 
	connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	
	printf("\t\t\t\t猪琦琦 聊天室 \n");
	hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID); 
	(void) time(&now);
    pts = ctime(&now);
	char buf[2000];
	sprintf(buf,"李荣: %s进入聊天室!",pts);
	(void) send(sock,buf, sizeof(buf), 0);
	while(1)
	{
		char buf1[2000];
		gets(buf1);
		(void) time(&now);
        pts = ctime(&now);
		if(!strcmp(buf1 ,"exit"))
		goto end; 
		sprintf(buf,"李荣: %s%s",pts,buf1);
		(void) send(sock,buf, sizeof(buf), 0);  //发送端发送信息
		(void) time(&now);
		pts = ctime(&now);
		printf("李荣： %s%s\n",pts,buf1);
	}
	    
	end:sprintf(buf,"李荣：%s退出聊天室!\n",pts);
		(void) send(sock,buf, sizeof(buf), 0);
		CloseHandle(hThread);
        closesocket(sock);
	    WSACleanup();                     /* 卸载某版本的DLL */  
	
	printf("按回车键继续...");
	getchar();
	return 0;                           /* exit */
}