#include<Winsock2.h>
#include<stdio.h>
#include<conio.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 4090
#define DATA_BUFFER 1024
#define END "End_Link"

void main(int argc,char *argv[])
{
	WSADATA wsaData;
	SOCKET sClient;
	int iPort=DEFAULT_PORT;
	int ser_iLen;
	char send[DATA_BUFFER],name[]="������";
	struct sockaddr_in ser;
	char ch;

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
	//�����������˵�ַ
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iPort);
	ser.sin_addr.s_addr=inet_addr(argv[1]);
    //�����ͻ������ݱ��׽ӿ�
	sClient=socket(AF_INET,SOCK_DGRAM,0);
	if(sClient==INVALID_SOCKET)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		return;
	}
	ser_iLen=sizeof(ser);
	//�����������ͨ�� ��������
	sendto(sClient,name,sizeof(name),0,(struct sockaddr*)&ser,ser_iLen);
	while(1)
	{
		ch=getch();
		if(ch==27) 
		{
			sendto(sClient,END,sizeof(END),0,(struct sockaddr*)&ser,ser_iLen);
			break;
		}
		gets(send);
		sendto(sClient,send,sizeof(send),0,(struct sockaddr*)&ser,ser_iLen);
	}
	closesocket(sClient);
	WSACleanup();
}