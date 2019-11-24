#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
#define thefile "config.txt"

typedef struct
{
	char UserName[200];//�ͻ��˺�
	char Password[200];//�ͻ�����
	int Log;//�Ƿ��½���׽ӿ��������е�λ��
}
UserData;//��¼�����û��Ľṹ������

UserData *data[64];
char User[1024],Pass[1024],us[1024],pa[1024];
int  usernum=0;//��¼�����û���Ŀ

//�жϿͻ��Ƿ�ע����߿ͻ���Ӧ���׽ӿ���Socket�����е�λ��
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
		if(strcmp(User,us)==0)//�û���ע��
		{
			if(strcmp(Pass,pa)==0) return 1;//������ȷ
			else return 2;//�������
		}
    }  
	fclose(fp);
	return 0;
}

void SaveData()//ע��ɹ�д���ļ�
{
	FILE *fp;
	///���������ļ�
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
	// ����һ����ʽ�׽ӿ�
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
	// ����һ���¼�����
	NewEvent = WSACreateEvent();
	// ��Listen�׽ӿ���ע���׽ӿ����Ӻ͹رյ������¼�
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
		// �������׽ӿ��ϵȴ������¼��ķ���
		//Index=0 ��ʾ�¿ͻ���½���������Ӧ�ͻ���socket�����е�λ��
		Index = WSAWaitForMultipleEvents(EventTotal, EventArray, FALSE, WSA_INFINITE, FALSE);
		if (WSAEnumNetworkEvents(SocketArray[Index - WSA_WAIT_EVENT_0],
							 EventArray[Index - WSA_WAIT_EVENT_0],
							 &NetworkEvents) == SOCKET_ERROR)
		{
			printf("%d/n", WSAGetLastError());
			printf("WSAEnumNetworkEvents()\n");
			return 0;
		}
							 
		// ���FD_ACCEPT
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_ACCEPT failed with error %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				break;
			}
			// �����µ����ӣ�����������׽ӿ�����
			Accept = accept(SocketArray[Index - WSA_WAIT_EVENT_0], (struct sockaddr*)&cli,&iLen);
			// ���׽ӿڵ���������ʱ���رո��׽ӿ�
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
			//���µ������׽ӿ�ע������ر��¼�
			WSAEventSelect(Accept, NewEvent, FD_READ | FD_CLOSE);
			EventArray[EventTotal] = NewEvent;
			SocketArray[EventTotal] = Accept;
			cliArray[EventTotal] = cli;
			EventTotal++;
		}
		
		// һ�´���FD_READ֪ͨ
		if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				WSACloseEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
				printf("FD_READ failed with error %d\n", NetworkEvents.iErrorCode[FD_READ_BIT]);
				break;
			}
			
			// ���׽ӿڶ�������
			recv(SocketArray[Index - WSA_WAIT_EVENT_0], str, sizeof(str), 0);

			printf("----------IP:[%s],port:[%d]-----------\n", 
				inet_ntoa(cliArray[Index - WSA_WAIT_EVENT_0].sin_addr),
				ntohs(cliArray[Index - WSA_WAIT_EVENT_0].sin_port));//���IP��ַ �˿ں�
		//	printf("%c,%s\n",str[0],str);
			if(str[0]=='1')
			{
				//ע��
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(Pass,str+i+1);
				int t=findUser();
				printf("%d\n",t);
				if(t==0)
				{//���û��������ڣ�����ע��
					SaveData();					
					printf("%s �û�ע��ɹ�\n",User);
					//--------------------------------------------------ע�����
					//���سɹ���Ϣ
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"ע��ɹ�!",sizeof("ע��ɹ�!"),0);
				}
				else
				{//fail
					printf("%s �û�ע��ʧ�� �û����Ѵ���\n",User);
					//-----------------------------------------------ע��ʧ��
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"�˺��Ѵ���!",sizeof("�˺��Ѵ���!"),0);
				}

			}
			else if(str[0]=='2')
			{
				//��½����Ϣ��ʽΪ   
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(Pass,str+i+1);
				int t=findUser();
				if(t!=0)
				{//�ҵ����û�
					if(t==1)
					{//������֤�ɹ�
						printf("%s ��½�ɹ�\n",User);
						data[usernum]=(UserData *)malloc(sizeof(UserData));
					    strcpy(data[usernum]->UserName,User);
					    strcpy(data[usernum]->Password,Pass);	
						data[usernum]->Log=Index - WSA_WAIT_EVENT_0;
						usernum++;
						printf("��������:%d��\n",usernum);
						send(SocketArray[Index - WSA_WAIT_EVENT_0],"��½�ɹ�!",sizeof("��½�ɹ�!"),0);
					}
					else
					{
						printf("%s ��½�������\n",User);
						send(SocketArray[Index - WSA_WAIT_EVENT_0],"�������!",sizeof("�������!"),0);
					}
				}
				else
				{
					printf("%s �û������ڣ���½ʧ��\n",User);
					send(SocketArray[Index - WSA_WAIT_EVENT_0],"�˺Ų�����!",sizeof("�˺Ų�����!"),0);
				}
			}
			else if(str[0]=='3')
			{	//�ͻ��˻�ȡ�����û�����������
				printf("��ȡ����������...\n");
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
			{//����Ⱥ��
				char bb[1024];
				strcpy(bb,str+2);
				printf("%s��������:%d��\n",bb,usernum);
				for(int i=1;i<=usernum;i++)
				{
					send(SocketArray[i],bb,sizeof(bb),0);
				}
			}
			else if(str[0]=='5')
			{//����˽��
				char bb[1024];
				int i;
				for(i=2;i<strlen(str);i++)
					if(str[i]=='@') break;
				str[i]='\0';
				strncpy(User,str+2,i-2);
				strcpy(bb,str+i+1);
				printf("%s��������:%d��\n",bb,usernum);
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
			{//�ͻ��뿪�����ң�����������ʾ
				 usernum--;
				 strcpy(User,str+2);
					 printf("%s �˳�����!\n��������:%d��\n",User,usernum);
			}
		}

		// ���´���FD_CLOSE֪ͨ
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
