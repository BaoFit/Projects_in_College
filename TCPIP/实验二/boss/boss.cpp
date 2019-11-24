#include<Winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 0624
#define DEFAULT_PO 0625
#define DATA_BUFFER 1024
#define LENGTH 100
#define END "End_Link"

void main()
{
	struct CLI
	{
		char ip[DATA_BUFFER];
		char ID[DATA_BUFFER];
	}client[LENGTH];
	int iPort1=DEFAULT_PORT,iPort2=DEFAULT_PO,size=0;
	WSADATA wsaData;
	SOCKET sListen,sAccept,sClient;
	char rev_buf[DATA_BUFFER],buf[DATA_BUFFER];
	struct sockaddr_in ser,cli,cli_ser;
	SYSTEMTIME sys;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Faild to load Winsock.\n");
		return;
	}
	sListen=socket(AF_INET,SOCK_STREAM,0);
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if(sListen==INVALID_SOCKET)
	{
		printf("socket() Failed:%d\n",WSAGetLastError());
		return;
	}
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iPort1);
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
	int iLen=sizeof(cli);
	memset(rev_buf,0,sizeof(rev_buf));
	while(1)
	{
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		if(sAccept==INVALID_SOCKET)
		{
			printf("accept()Faild:%d\n",WSAGetLastError());
			break;
		}
		printf("\n-----------IP:[%s],port[%d]-----------------\n",
			inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		recv(sAccept,rev_buf,sizeof(rev_buf),0);
		if(strcmp(rev_buf,"come_in")==0)
		{
			recv(sAccept,rev_buf,sizeof(rev_buf),0);
			printf("%s进入聊天室!\n",rev_buIDf);
			strcpy(client[size].,rev_buf);
			strcpy(client[size].ip,inet_ntoa(cli.sin_addr));
			size++;
			printf("在线%d人\n",size);
		}
		else if(strcmp(rev_buf,"come_out")==0)
		{
			recv(sAccept,rev_buf,sizeof(rev_buf),0);
			printf("&s退出聊天室!\n",rev_buf);
			for(int i=0;i<size;i++)
			{
				if(strcmp(rev_buf,client[i].ID)==0)
				{
					strcpy(client[i].ID,client[size-1].ID);
					strcpy(client[i].ip,client[size-1].ip);
					break;
				}
			}
			size--;
			printf("在线%d人\n",size);
		}
		else
		{
			recv(sAccept,buf,sizeof(buf),0);
			recv(sAccept,rev_buf,sizeof(rev_buf),0);
			GetLocalTime(&sys);
			printf("%s:  %4d/%02d/%02d %02d:%02d:%02d\n%s",
			buf,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,rev_buf);
			printf("在线%d人\n",size);
			for(int i=0;i<size;i++)
			{	
				cli_ser.sin_family=AF_INET;
				cli_ser.sin_port=htons(iPort2);
				cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
				connect(sClient,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				send(sClient,buf,sizeof(buf),0);
				send(sClient,rev_buf,sizeof(rev_buf),0);
				closesocket(sClient);
			}
		}
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
}


















