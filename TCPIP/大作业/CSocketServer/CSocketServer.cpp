#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
#define thefile "config.txt"

typedef struct
{
	char UserName[200];//客户账号
	char Password[200];//客户密码
	int Log;//是否登陆和套接口在数组中的位置
}
UserData;//记录在线用户的结构体数组

UserData *data[64];
char User[1024],Pass[1024],us[1024],pa[1024];
int  usernum=0;//记录在线用户数目

//判断客户是否注册或者客户对应的套接口在Socket数组中的位置
int findUser()
{
	FILE *fp;
	char p[1024];
	int i,j;
	fp = fopen(thefile, "r");
    while((fgets(p,1024,fp))!=NULL)  
    { 
		printf("p:%s!\n",p);
		for(i=0;i<strlen(p);i++)
		{
			if(p[i]==',')
				break;
		}
		for(j=0;j<strlen(p);j++)
		{
			if(p[j]=='\n')
				break;
		}
		p[i]=='\0';
		p[j]=='\0';
		memset(pa,0,sizeof(pa));
		memset(us,0,sizeof(us));
		strncpy(us,p,i);
		strncpy(pa,p+i+1,j-i-1);
		printf("us:%s!,pa%s!\n",us,pa);
		if(strcmp(User,us)==0)//用户已注册
		{
			if(strcmp(Pass,pa)==0) return 1;//密码正确
			else return 2;//密码错误
		}
    }  
	fclose(fp);
	return 0;
}

void SaveData()//注册成功写入文件
{
	FILE *fp;
	///建立配置文件
	fp=fopen(thefile,"w");
	fputs(User,fp);
	fputs(",",fp);
	fputs(Pass,fp); 
	fprintf(fp,"\n");
	fclose(fp);
}

int main()
{
	//
	char buffer[1024],str[1024];
	WSADATA wsaData;
	struct sockaddr_in InternetAddr,cli,cliArray[WSA_MAXIMUM_WAIT_EVENTS];
	int iLen;
	iLen=sizeof(cli);
	SOCKET sSocket,Accept, Listen,sClient,SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
	
	WSANETWORKEVENTS NetworkEvents;
	WSAEVENT NewEvent,EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	
	DWORD Index,EventTotal = 0;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup()\n");
		return 0;
	}
	// 创建一个流式套接口
	Listen = socket(AF_INET, SOCK_STREAM, 0);
	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(5050);
	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind()\n");
		return 0;
	}
	printf("----------------------\n");
	printf("Server Waiting\n");
	printf("----------------------\n");
	// 创建一个事件对象
	NewEvent = WSACreateEvent();
	// 在Listen套接口上注册套接口连接和关闭的网络事件
	WSAEventSelect(Listen, NewEvent, FD_ACCEPT | FD_CLOSE);
	
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		printf("listen()\n");
		return 0;
	}
	SocketArray[EventTotal] = Listen;
	EventArray[EventTotal] = NewEvent;
	EventTotal++;
	
	while (true)
	{
		// 在所有套接口上等待网络事件的发生
		//Index=0 表示新客户登陆，其他则对应客户在socket数组中的位置
		Index = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, WSA_INFINITE, FALSE);
		if (WSAEnumNetworkEvents(SocketArray[Index - WSA_WAIT_EVENT_0],
							 EventArray[Index - WSA_WAIT_EVENT_0],
							 &NetworkEvents) == SOCKET_ERROR)
		{
			printf("%d/n", WSAGetLastError());
			printf("WSAEnumNetworkEvents()\n");
			return 0;
		}
							 
		// 检查FD_ACCEPT
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_ACCEPT failed with error %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				break;
			}
			// 接收新的连接，并将其存入套接口数组
			Accept = accept(SocketArray[Index - WSA_WAIT_EVENT_0], (struct sockaddr*)&cli,&iLen);
			// 当套接口的数量超界时，关闭该套接口
			if (EventTotal > WSA_MAXIMUM_WAIT_EVENTS)
			{
				printf("Too many connections");
				closesocket(Accept);
				break;
			}
			NewEvent = WSACreateEvent();
			if (NewEvent == WSA_INVALID_EVENT)
			{
				printf("WSACreateEvent()\n");
				break;
			}
			//给新的连接套接口注册读、关闭事件
			WSAEventSelect(Accept, NewEvent, FD_READ | FD_CLOSE);
			EventArray[EventTotal] = NewEvent;
			SocketArray[EventTotal] = Accept;
			cliArray[EventTotal] = cli;
			EventTotal++;
		}
		
		// 一下处理FD_READ通知
		if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_READ failed with error %d\n", NetworkEvents.iErrorCode[FD_READ_BIT]);
				break;
			}
			
			// 从套接口读入数据
			recv(SocketArray[Index - WSA_WAIT_EVENT_0], str, sizeof(str), 0);

			printf("----------IP:[%s],port:[%d]-----------\n", 
				inet_ntoa(cliArray[Index - WSA_WAIT_EVENT_0].sin_addr),
				ntohs(cliArray[Index - WSA_WAIT_EVENT_0].sin_port));//输出IP地址 端口号
		//	printf("%c,%s\n",str[0],str);
			if(str[0]=='1')
			{
				//注册
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(Pass,str+i+1);
				int t=findUser();
				printf("%d\n",t);
				if(t==0)
				{//该用户名不存在，可以注册
					SaveData();					
					printf("%s 用户注册成功\n",User);
					//--------------------------------------------------注册完成
					//返回成功信息
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"注册成功!",sizeof("注册成功!"),0);
				}
				else
				{//fail
					printf("%s 用户注册失败 用户名已存在\n",User);
					//-----------------------------------------------注册失败
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"账号已存在!",sizeof("账号已存在!"),0);
				}

			}
			else if(str[0]=='2')
			{
				//登陆的消息格式为   
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(Pass,str+i+1);
				int t=findUser();
				if(t!=0)
				{//找到该用户
					if(t==1)
					{//密码验证成功
						printf("%s 登陆成功\n",User);
						data[usernum]=(UserData *)malloc(sizeof(UserData));
					    strcpy(data[usernum]->UserName,User);
					    strcpy(data[usernum]->Password,Pass);	
						data[usernum]->Log=Index - WSA_WAIT_EVENT_0;
						usernum++;
						printf("在线人数:%d人\n",usernum);
						send(SocketArray[Index - WSA_WAIT_EVENT_0],"登陆成功!",sizeof("登陆成功!"),0);
					}
					else
					{
						printf("%s 登陆密码错误\n",User);
						send(SocketArray[Index - WSA_WAIT_EVENT_0],"密码错误!",sizeof("密码错误!"),0);
					}
				}
				else
				{
					printf("%s 用户不存在，登陆失败\n",User);
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"账号不存在!",sizeof("账号不存在!"),0);
				}
			}
			else if(str[0]=='3')
			{	//客户端获取在线用户和在线人数
				printf("获取在线人数中...\n");
				char send_buf[1024]="@";
				itoa(usernum,buffer,10);
				strcat(send_buf,buffer);
				for(int p=0;p<usernum;p++)
				{
					strcat(send_buf,"@");
					strcat(send_buf,data[p]->UserName);
				}
				for(int q=1;q<=usernum;q++)
				{
					send(SocketArray[q],send_buf,sizeof(send_buf),0);
				}
			}
			else if(str[0]=='4')
			{//处理群聊
				char bb[1024];
				strcpy(bb,str+2);
				printf("%s在线人数:%d人\n",bb,usernum);
				for(int i=1;i<=usernum;i++)
				{
					send(SocketArray[i],bb,sizeof(bb),0);
				}
			}
			else if(str[0]=='5')
			{//处理私聊
				char bb[1024];
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(bb,str+i+1);
				printf("%s在线人数:%d人\n",bb,usernum);
				for(i=1;i<=usernum;i++)
				{
					if(strcmp(User,data[i-1]->UserName)==0)
					{
						send(SocketArray[data[i-1]->Log],bb,sizeof(bb),0);
						break;
					}
				}
			}
			else
			{//客户离开聊天室，服务器端显示
				 usernum--;
				 strcpy(User,str+2);
					 printf("%s 退出聊天!\n在线人数:%d人\n",User,usernum);
			}
		}

		// 以下处理FD_CLOSE通知
		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				closesocket(SocketArray[Index - WSA_WAIT_EVENT_0]);
				 for(int j=Index - WSA_WAIT_EVENT_0+1;j<EventTotal;j++)
				 {
				    EventArray[j-1] = EventArray[j];
				    SocketArray[j-1] = SocketArray[j];
					cliArray[j-1]=cliArray[j];
				}
				 EventTotal--;
				 for(int i=1;i<=usernum;i++)
				{
					send(SocketArray[i],"#",sizeof("#"),0);
				}
			}
		}	
	}
	WSACleanup();
	return 0;
}
