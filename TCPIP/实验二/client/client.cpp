#include<Winsock2.h>
#include<stdio.h>
#include<conio.h>
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 0624
#define DATA_BUFFER 1024

void main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET sClient;
	int iPort=DEFAULT_PORT;
	char send_buf[DATA_BUFFER],ch;
	struct sockaddr_in ser;
	if(argc<2)
	{
		printf("Usage:client[server IP address]\n");
		return;
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
		return;
	}
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iPort);
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if(sClient==INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return;
	}
	if(connect(sClient,(struct sockaddr*)&ser,sizeof(ser))==INVALID_SOCKET)
	{
		printf("connect()Failed:%d\n",WSAGetLastError());
		return;
	}
	send(sClient,"come_in",sizeof("come_in"),0);
	send(sClient,"李荣",sizeof("李荣"),0);
	while(1)
	{	
		ch=getch();
		if(ch==27) 
		{
			send(sClient,"come_out",sizeof("come_out"),0);
			send(sClient,"李荣",sizeof("李荣"),0);
			break;
		}
		gets(send_buf);
		send(sClient,"qunliao",sizeof("qunliao"),0);
		send(sClient,send_buf,sizeof(send_buf),0);
	}
	closesocket(sClient);
	WSACleanup();
}