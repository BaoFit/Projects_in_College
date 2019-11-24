#include<Winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")

#define DEFAULT_PORT 4499
#define BUFFER_LENGTH 1024
#define END "End_Link"
#define LENGTH 100

static char *ID;
static char *PSW;
FILE *fp;

int Read(char *s)
{
	int n=0;
	char p[BUFFER_LENGTH];
	fp = fopen("data.txt", "r");
    while((fgets(p,BUFFER_LENGTH,fp))!=NULL)  
    { 
	//	printf("%s,%s,%d\n",p,s,strcmp(p,s));
		if(strcmp(p,s)==1) 
		{
			ID=s;
			fgets(p,BUFFER_LENGTH,fp);
			PSW=p;
			fclose(fp);
			n=1;
			break;
		}
		fgets(p,BUFFER_LENGTH,fp);
    }  
	fclose(fp);
	return n;
}

void main()
{
	struct CLI
	{
		char *name;
		char *ip;
	}client[LENGTH];
	int iPort=DEFAULT_PORT,iLen,i,size=0,n;
	WSADATA wsaData;
	SOCKET sSocket;
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
		if(strcmp(recv_buf,"zhuce")==0)
		{
			recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
			if(Read(recv_buf)==1)
			{
				printf("%s注册失败，账号已存在!\n",recv_buf);
				sendto(sSocket,"ID_exist",sizeof("ID_exist"),0,(struct sockaddr*)&cli,sizeof(cli));
				recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
			}
			else
			{
				printf("%s注册成功!\n",recv_buf);
				fp=fopen("data.txt","a");
				fputs(recv_buf,fp);
				fputs("\n",fp);
				recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
				fputs(recv_buf,fp);   
				fputs("\n",fp);
				fclose(fp);
				sendto(sSocket,"zhuce_succeed",sizeof("zhuce_succeed"),0,(struct sockaddr*)&cli,sizeof(cli));
			}
		}
		else if(strcmp(recv_buf,"denglu")==0)
		{
			recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
			if(Read(recv_buf)==0)
			{
				printf("%s登录失败，账号不存在!\n",recv_buf);
				sendto(sSocket,"ID_notexist",sizeof("ID_notexist"),0,(struct sockaddr*)&cli,sizeof(cli));	
				recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
			}
			else
			{
				printf("%s",ID);
				client[size].name=ID;
				recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
				if(strcmp(PSW,recv_buf)!=1)
				{
					printf("登录失败，密码错误!\n");
					sendto(sSocket,"psw_wrong",sizeof("psw_wrong"),0,(struct sockaddr*)&cli,sizeof(cli));
				}
				else
				{
					client[size].ip=inet_ntoa(cli.sin_addr);
					size++;
					printf("进入聊天室!\n在线%d人\n",size);
					sendto(sSocket,"denglu_succeed",sizeof("denglu_succeed"),0,(struct sockaddr*)&cli,sizeof(cli));
				}
			}
		}
		else
		{
			char cc[BUFFER_LENGTH];
			strcpy(cc,recv_buf);
			printf("%s",recv_buf);
			recvfrom(sSocket,recv_buf,BUFFER_LENGTH,0,(SOCKADDR*)&cli,&iLen);
			if(strcmp(recv_buf,END)==0)
			{
				printf("退出聊天室!\n");;
				for(i=0;i<size;i++)
					if(strcmp(inet_ntoa(cli.sin_addr),client[i].ip)==0)
					{
						client[i].name=client[size-1].name;
						client[i].ip=client[size-1].ip;
						break;
					}
				size--;
				printf("在线人数%d人\n",size);	
				for(i=0;i<size;i++)
				{
					cli_ser.sin_family=AF_INET;
					cli_ser.sin_port=htons(iPort);
					cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
					sendto(sSocket,cc,sizeof(cc),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
					sendto(sSocket,"退出聊天室!",sizeof("退出聊天室!"),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				}
			}
			else
			{
				GetLocalTime(&sys);
				printf(":  %4d/%02d/%02d %02d:%02d:%02d\n%s\n",
				sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,recv_buf);
				printf("在线人数%d人\n",size);
				for(i=0;i<size;i++)
				{
					cli_ser.sin_family=AF_INET;
					cli_ser.sin_port=htons(iPort);
					cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
					sendto(sSocket,cc,sizeof(cc),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
					sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				}
			}
		}
	}
	closesocket(sSocket);
	WSACleanup();
}