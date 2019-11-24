#include<Winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 4090
#define BUFFER_LENGTH 1024
#define LENGTH 100
#define END "End_Link"

void main()
{	
	struct CLI
	{
		char name[BUFFER_LENGTH];
		char ip[20];
	}client[LENGTH];

	int iPort=DEFAULT_PORT,iLen;
	WSADATA wsaData;
	SOCKET sSocket;
	int i,size=0,n; 
	char recv_buf[BUFFER_LENGTH];  //接收数据的缓冲区
	struct sockaddr_in ser,cli,cli_ser;
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
		n=-1;
		recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
		printf("\n----IP[%s],iPort[%d]----\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		for(i=0;i<size;i++)
		{
			if(strcmp(inet_ntoa(cli.sin_addr),client[i].ip)==0) 
			{
				n=i;	
				break;
			}
		}
		if(strcmp(recv_buf,END)==0)
		{
			printf("%s退出聊天室!\n",client[n].name);
			size--;
			printf("在线人数%d人\n",size);
			strcpy(client[n].name,client[size].name);
			strcpy(client[n].ip,client[size].ip);
		}
		else if(n==-1)
		{
			printf("%s加入聊天室!\n",recv_buf);
			strcpy(client[size].name,recv_buf);
			strncpy(client[size].ip,inet_ntoa(cli.sin_addr),19);
			client[size].ip[19]='\0';
			size++;
			printf("在线人数%d人\n",size);
		}
		else
		{
			GetLocalTime(&sys);
			printf("%s:  %4d/%02d/%02d %02d:%02d:%02d\n%s\n",client[n].name,
			sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,recv_buf);
			for(int i=0;i<size;i++)
			{
				cli_ser.sin_family=AF_INET;
				cli_ser.sin_port=htons(iPort);
				cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
				sendto(sSocket,client[n].name,sizeof(client[n].name),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
			}
		}
	}
	closesocket(sSocket);
	WSACleanup();
}