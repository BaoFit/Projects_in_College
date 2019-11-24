#include<Winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
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
		char name[BUFFER_LENGTH];
		char ip[BUFFER_LENGTH];
	}client[LENGTH];
	int iPort=DEFAULT_PORT,iLen,i,size=0,n;
	WSADATA wsaData;
	SOCKET sListen,sAccept;
	char recv_buf[BUFFER_LENGTH];  //接收数据的缓冲区
	struct sockaddr_in ser,cli,cli_ser;
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
	ser.sin_port=htons(4490);
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
		sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
		printf("开始了\n");
		if(sAccept==INVALID_SOCKET)
		{
			printf("accept()Faild:%d\n",WSAGetLastError());
			break;
		}
		n=-1;
		printf("shibailema\n");
		recv(sAccept,recv_buf,sizeof(recv_buf),0);
		printf("\n----IP[%s],iPort[%d]----\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		if(strcmp(recv_buf,"zhuce")==0)
		{
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			if(Read(recv_buf)==1)
			{
				printf("%s注册失败，账号已存在!\n",recv_buf);
				send(sAccept,"ID_exist",sizeof("ID_exist"),0);
				recv(sAccept,recv_buf,sizeof(recv_buf),0);
			}
			else
			{
				printf("%s注册成功!\n",recv_buf);
				fp=fopen("data.txt","a");
				fputs(recv_buf,fp);
				fputs("\n",fp);
				recv(sAccept,recv_buf,sizeof(recv_buf),0);
				fputs(recv_buf,fp);   
				fputs("\n",fp);
				fclose(fp);
				send(sAccept,"zhuce_succeed",sizeof("zhuce_succeed"),0);
			}
		}
		else if(strcmp(recv_buf,"denglu")==0)
		{
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			if(Read(recv_buf)==0)
			{
				printf("%s登录失败，账号不存在!\n",recv_buf);
				send(sAccept,"ID_notexist",sizeof("ID_notexist"),0);	
				recv(sAccept,recv_buf,sizeof(recv_buf),0);
			}
			else
			{
				strcpy(client[size].name,recv_buf);
				printf("%s",client[size].name);
				recv(sAccept,recv_buf,sizeof(recv_buf),0);
				if(strcmp(PSW,recv_buf)!=1)
				{
					printf("登录失败，密码错误!\n");
					send(sAccept,"psw_wrong",sizeof("psw_wrong"),0);
				}
				else
				{
					strcpy(client[size].ip,inet_ntoa(cli.sin_addr));
					size++;
					printf("进入聊天室!\n在线%d人\n",size);
					send(sAccept,"denglu_succeed",sizeof("denglu_succeed"),0);
				}
			}
		}
		else if(strcmp(recv_buf,END)==0)
		{
			//char cc[BUFFER_LENGTH];
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
		//	strcpy(cc,recv_buf);
			printf("%s退出聊天室!\n",recv_buf);
			for(i=0;i<size;i++)
				if(inet_ntoa(cli.sin_addr)==client[i].ip)
				{
					strcpy(client[i].name,client[size-1].name);
					strcpy(client[i].ip,client[size-1].ip);
					break;
				}
			size--;
			printf("在线人数%d人\n",size);	
		/*	for(i=0;i<size;i++)
			{
				cli_ser.sin_family=AF_INET;
				cli_ser.sin_port=htons(iPort);
				cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
				sendto(sSocket,cc,sizeof(cc),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				sendto(sSocket,"通知",sizeof("通知"),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				sendto(sSocket,"退出聊天室!",sizeof("退出聊天室!"),0,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
			}*/
		}
		else if(strcmp(recv_buf,"qunliao")==0)
		{
			char cc[BUFFER_LENGTH];
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			strcpy(cc,recv_buf);
			printf("%s",recv_buf);
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			GetLocalTime(&sys);
			printf(":  %4d/%02d/%02d %02d:%02d:%02d   [群聊]\n%s\n",
				sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,recv_buf);
			printf("在线人数%d人\n",size);
			for(i=0;i<size;i++)
			{
				closesocket(sAccept);
				cli_ser.sin_family=AF_INET;
				cli_ser.sin_port=htons(iPort);
				cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
				sAccept=socket(AF_INET,SOCK_STREAM,0);
				connect(sAccept,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
				send(sAccept,cc,sizeof(cc),0);
				send(sAccept,"群聊",sizeof("群聊"),0);
				send(sAccept,recv_buf,sizeof(recv_buf),0);
			}
		}
		else if(strcmp(recv_buf,"getOnMember")==0)
		{
			printf("获取在线成员\n");
			if(size==0)
				send(sAccept,"Empty",sizeof("Empty"),0);
			else
			{
				for(i=0;i<size;i++)
					send(sAccept,client[i].name,sizeof(client[i].name),0);
			}
			send(sAccept,"end",sizeof("end"),0);
		}
		else
		{
			char cc[BUFFER_LENGTH];
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			strcpy(cc,recv_buf);
			printf("%s",recv_buf);
			recv(sAccept,recv_buf,sizeof(recv_buf),0);
			GetLocalTime(&sys);
			printf(":  %4d/%02d/%02d %02d:%02d:%02d   [私聊%s]\n",
				sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,recv_buf);
			for(i=0;i<size;i++)
			{
				if(strcmp(client[i].name,recv_buf)==0)
				{
					closesocket(sAccept);
					cli_ser.sin_family=AF_INET;
					cli_ser.sin_port=htons(iPort);
					cli_ser.sin_addr.s_addr=inet_addr(client[i].ip);
					recv(sAccept,recv_buf,sizeof(recv_buf),0);
					printf("%s\n",recv_buf);
					printf("在线人数%d人\n",size);
					sAccept=socket(AF_INET,SOCK_STREAM,0);
					connect(sAccept,(struct sockaddr*)&cli_ser,sizeof(cli_ser));
					send(sAccept,cc,sizeof(cc),0);
					send(sAccept,"私聊",sizeof("私聊"),0);
					send(sAccept,recv_buf,sizeof(recv_buf),0);
					break;
				}
			}
		}
		closesocket(sAccept);
	}
	closesocket(sListen);
	WSACleanup();
}