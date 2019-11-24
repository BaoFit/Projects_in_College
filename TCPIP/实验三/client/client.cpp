#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <math.h>

#define    BUFLEN        2000                  // ��������С
#define WSVERS        MAKEWORD(2, 0)        // ָ���汾2.0 
#pragma comment(lib,"ws2_32.lib")         // ָ��winsock 2.0 Llibrary

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

	while(1)                //���ն˽�����Ϣ
	{
		int cc = recv(sock, buf, BUFLEN, 0);   //ccΪ���յ��ַ���  
		if(cc == SOCKET_ERROR|| cc == 0)
		{
		//	printf("Error: %d.----",GetLastError());
		//	printf("��������Ͽ����ӣ�\n");
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
	WSAStartup(WSVERS, &wsadata);       /* ����ĳ�汾Socket��DLL        */        
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((u_short)atoi(service));    //atoi����asciiת��Ϊint. htons��������(host)ת��Ϊ������(network), s--short
	sin.sin_addr.s_addr = inet_addr(host);           //���hostΪ��������Ҫ���ú���gethostbyname������ת��ΪIP��ַ
  
	sock = socket(PF_INET, SOCK_STREAM,0);
 
	connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	
	printf("\t\t\t\t������ ������ \n");
	hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID); 
	(void) time(&now);
    pts = ctime(&now);
	char buf[2000];
	sprintf(buf,"����: %s����������!",pts);
	(void) send(sock,buf, sizeof(buf), 0);
	while(1)
	{
		char buf1[2000];
		gets(buf1);
		(void) time(&now);
        pts = ctime(&now);
		if(!strcmp(buf1 ,"exit"))
		goto end; 
		sprintf(buf,"����: %s%s",pts,buf1);
		(void) send(sock,buf, sizeof(buf), 0);  //���Ͷ˷�����Ϣ
		(void) time(&now);
		pts = ctime(&now);
		printf("���٣� %s%s\n",pts,buf1);
	}
	    
	end:sprintf(buf,"���٣�%s�˳�������!\n",pts);
		(void) send(sock,buf, sizeof(buf), 0);
		CloseHandle(hThread);
        closesocket(sock);
	    WSACleanup();                     /* ж��ĳ�汾��DLL */  
	
	printf("���س�������...");
	getchar();
	return 0;                           /* exit */
}