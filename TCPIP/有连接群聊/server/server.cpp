#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"WS2_32")  
#define BUFFER_SIZE 1024

int main()
{
	struct sockaddr_in cli;
	struct sockaddr_in cliArray[WSA_MAXIMUM_WAIT_EVENTS];
	int iLen;
	iLen=sizeof(cli);
	WSADATA wsaData;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in InternetAddr;
	SOCKET SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
	
	WSANETWORKEVENTS NetworkEvents;
	WSAEVENT NewEvent;
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	
	SOCKET Accept, Listen;
	
	DWORD EventTotal = 0;
	DWORD Index;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup()/n");
		return 0;
	}
	// 创建一个流式套接口
	Listen = socket(AF_INET, SOCK_STREAM, 0);
	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(5050);
	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind()/n");
		return 0;
	}
	// 创建一个事件对象
	NewEvent = WSACreateEvent();
	// 在Listen套接口上注册套接口连接和关闭的网络事件
	WSAEventSelect(Listen, NewEvent, FD_ACCEPT | FD_CLOSE);
	
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		printf("listen()/n");
		return 0;
	}
	SocketArray[EventTotal] = Listen;
	EventArray[EventTotal] = NewEvent;
	EventTotal++;
	while (true)
	{
		// 在所有套接口上等待网络事件的发生
		Index = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, WSA_INFINITE, FALSE);
		if (WSAEnumNetworkEvents(SocketArray[Index - WSA_WAIT_EVENT_0],
							 EventArray[Index - WSA_WAIT_EVENT_0],
							 &NetworkEvents) == SOCKET_ERROR)
		{
			printf("%d\n", WSAGetLastError());
			printf("WSAEnumNetworkEvents()/n");
			return 0;
		}
							 
		// 检查FD_ACCEPT
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_ACCEPT failed with error %d/n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				break;
			}
			// 接收新的连接，并将其存入套接口数组
			Accept = accept(SocketArray[Index - WSA_WAIT_EVENT_0],(struct sockaddr*)&cli,&iLen);
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
				printf("FD_READ failed with error %d/n", NetworkEvents.iErrorCode[FD_READ_BIT]);
				break;
			}
			
			// 从套接口读入数据
			recv(SocketArray[Index - WSA_WAIT_EVENT_0], buffer, sizeof(buffer), 0);
			printf("--------------IP:[%s],port:[%d]----------------\n", 
				inet_ntoa(cliArray[Index - WSA_WAIT_EVENT_0].sin_addr),ntohs(cliArray[Index - WSA_WAIT_EVENT_0].sin_port));
			if(strcmp(buffer,"exit")==0)
			{
				recv(SocketArray[Index - WSA_WAIT_EVENT_0], buffer, sizeof(buffer), 0);
				printf("%s",buffer);
				printf("在线%d人\n",EventTotal-2);
			}
			else
			{
				printf("%s", buffer);
				printf("在线%d人\n",EventTotal-1);
			}
			for(int i=1;i<EventTotal;i++)
				send(SocketArray[i],buffer,sizeof(buffer),0);
		}
		// 以下处理FD_CLOSE通知
		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				closesocket(SocketArray[Index - WSA_WAIT_EVENT_0]);
				 for(int i=Index - WSA_WAIT_EVENT_0+1;i<EventTotal;i++)
				 {
				    EventArray[i-1] = EventArray[i];
				   SocketArray[i-1] = SocketArray[i];
					  cliArray[i-1]=cliArray[i];
				}
				 EventTotal--;
			}
		}
	}
	WSACleanup();
	return 0;
}