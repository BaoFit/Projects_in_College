#include <winsock2.h>  
#pragma comment(lib,"WS2_32")  
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <process.h>

WSANETWORKEVENTS NetworkEvents;
WSAEVENT NewEvent,EventArray[WSA_MAXIMUM_WAIT_EVENTS];	
DWORD EventTotal = 0,Index;
struct  sockaddr_in  Sadd,C1add;
SOCKET c1,SocketArray[WSA_MAXIMUM_WAIT_EVENTS];  
char *pts,buffer[1024],S_buf[1024],buf[1024]; 
unsigned threadID;
HANDLE hThread;
unsigned int __stdcall Chat(PVOID PM ) 
{
	while(true)
	{
		Index = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, WSA_INFINITE, FALSE);
		if (WSAEnumNetworkEvents(SocketArray[Index - WSA_WAIT_EVENT_0],
							 EventArray[Index - WSA_WAIT_EVENT_0],
							 &NetworkEvents) == SOCKET_ERROR)
		{
			printf("%d\n", WSAGetLastError());
			printf("WSAEnumNetworkEvents()/n");
			return 0;
		}
		// һ�´���FD_READ֪ͨ
		if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_READ failed with error %d/n", NetworkEvents.iErrorCode[FD_READ_BIT]);
				return 0;
			}
			// ���׽ӿڶ�������
			recv(SocketArray[Index - WSA_WAIT_EVENT_0], buffer, sizeof(buffer), 0);
			printf("%s", buffer);
		}
	}
}

int main()  
{     
    WSADATA wsaData;  
    WORD wVersionRequested=MAKEWORD(2,2);    
    if(WSAStartup(wVersionRequested,&wsaData)!=0)             
    {   printf("WSAStartup() Failed,Error=%d\n",WSAGetLastError());     
        return 1;  
    }        
//������ʽ�׽���
    c1 = socket(AF_INET, SOCK_STREAM,0);  
    if(c1 == INVALID_SOCKET)      
    {   
		printf("socket() Failed,Error=%d\n",WSAGetLastError());  
        return 1;  
    }       
//�󶨱��ص�ַ  
    C1add.sin_family=AF_INET;  
    C1add.sin_port=htons(2222);  
    C1add.sin_addr.s_addr=htonl(INADDR_ANY);      
    if(bind(c1,(sockaddr*)&C1add,sizeof(C1add))==SOCKET_ERROR)    
    {   
		printf("bind() Failed,Error=%d\n",WSAGetLastError());   
        return 1;  
    }    
//��������    
    Sadd.sin_family=AF_INET;  
    Sadd.sin_port=htons(5050);    
    Sadd.sin_addr.s_addr=inet_addr("192.168.43.241");   
    if(connect(c1, (sockaddr*)&Sadd, sizeof(Sadd)) == -1)  
    {   
		printf(" Failed connect(),Error=[%d]\n",WSAGetLastError());         
        return 1;  
    } 	
	//ע���¼�
	NewEvent = WSACreateEvent();
	WSAEventSelect(c1, NewEvent, FD_READ);
	SocketArray[EventTotal] = c1;
	EventArray[EventTotal] = NewEvent;
	EventTotal++;   
	hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID);
	time_t    now;
	(void) time(&now);
	pts = ctime(&now);
	sprintf(buf,"����: %s����������!\n",pts);
	send(c1,buf,sizeof(buf),0);
    while(true)  //------ѭ������------  
    {  	
	// ���´���FD_WRITE֪ͨ
		gets(S_buf);
		if(strcmp(S_buf,"exit")==0)
		{
			time_t    now;
			(void) time(&now);
			pts = ctime(&now);
			sprintf(buf,"����: %s�˳�������!\n",pts);
			send(c1,S_buf,sizeof(S_buf),0);
			send(c1,buf,sizeof(buf),0);
			printf("%s",buf);
			break; 
		}
		else
		{
			time_t    now;
			(void) time(&now);
			pts = ctime(&now);
			sprintf(buf,"����: %s%s\n",pts,S_buf);
			send(c1,buf,sizeof(buf),0); 
		}   
	}
	CloseHandle(hThread);
    closesocket(c1);          
    WSACleanup();    
    return 0;  
} 