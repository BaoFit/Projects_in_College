#include<Winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 4499
#define BUFFER_LENGTH 1024
#define END "End_Link"

void main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;

	SOCKET sListen,sAccept;

	int iLen; //客户地址长度
	char recv_buf[BUFFER_LENGTH];  //接收数据的缓冲区

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
	memset(recv_buf,0,sizeof(recv_buf));
	while(1)
	{
		GetLocalTime(&sys);
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		recv(sAccept,recv_buf,sizeof(recv_buf),0);
	    printf("%s",recv_buf);
		recv(sAccept,recv_buf,sizeof(recv_buf),0);
		printf(":  %4d/%02d/%02d %02d:%02d:%02d    [%s]\n",
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,recv_buf);
		recv(sAccept,recv_buf,sizeof(recv_buf),0);
		printf("%s\n",recv_buf);
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
}

