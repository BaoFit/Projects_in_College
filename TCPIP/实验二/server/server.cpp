#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 0625
#define DATA_BUFFER 1024

void main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;
	SOCKET sListen,sAccept;
	int iLen;
	char rev_buf[DATA_BUFFER];
	struct sockaddr_in ser,cli;
	SYSTEMTIME sys;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Faild to load Winsock.\n");
		return;
	}
	sListen=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
		printf("socket() Failed:%d\n",WSAGetLastError());
		return;
	}
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iPort);
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return;
	}
	if(listen(sListen,5)==SOCKET_ERROR)
	{
		printf("listen()Failed:%d\n",WSAGetLastError());
		return;
	}
	iLen=sizeof(cli);
	memset(rev_buf,0,sizeof(rev_buf));
	while(1)
	{
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		if(sAccept==INVALID_SOCKET)
		{
			printf("accept()Faild:%d\n",WSAGetLastError());
			break;
		}
		recv(sAccept,rev_buf,sizeof(rev_buf),0);
		GetLocalTime(&sys);
		printf("%s:  %4d/%02d/%02d %02d:%02d:%02d\n",
		rev_buf,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
		recv(sAccept,rev_buf,sizeof(rev_buf),0);
		printf("%s\n",rev_buf);
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
}

