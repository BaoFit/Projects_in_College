#include<Winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 4090
#define BUFFER_LENGTH 1024
#define END "End_Link"

void main()
{
	int iPort=DEFAULT_PORT;
	WSADATA wsaData;

	SOCKET sSocket;

	int iLen; //客户地址长度
	char recv_buf[BUFFER_LENGTH];  //接收数据的缓冲区

	struct sockaddr_in ser,cli;

	SYSTEMTIME sys;

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Faild to load Winsock.\n");
		return;
	}

	sSocket=socket(AF_INET,SOCK_DGRAM,0);

	if(sSocket==INVALID_SOCKET)
	{
		printf("socket() Failed:%d\n",WSAGetLastError());
		return;
	}

	ser.sin_family=AF_INET;

	ser.sin_port=htons(iPort);

	ser.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sSocket,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		return;
	}
	iLen=sizeof(cli);
	memset(recv_buf,0,sizeof(recv_buf));
	while(1)
	{
		GetLocalTime(&sys);
		recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
		printf("%s:  %4d/%02d/%02d %02d:%02d:%02d\n",recv_buf,
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
		recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
		printf("%s\n",recv_buf);
	}
	closesocket(sSocket);
	WSACleanup();
}

