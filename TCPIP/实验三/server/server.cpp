/* TCPdtd.cpp - main, TCPdaytimed */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <windows.h>
#include <process.h>
#include <math.h>

#define QLEN       5
#define    WSVERS    MAKEWORD(2, 0)
#define    BUFLEN    2000             
#pragma comment(lib,"ws2_32.lib")  

    SOCKET    msock, ssock;            
    SOCKET    sockets[100] = {NULL};
     
     int cc,number,size=0;
     char    *pts;                    
     time_t    now;                    
     char buf[2000];                      
     char *input;
     HANDLE hThread1,hThread[100] = {NULL};
	 unsigned int threadID,ThreadID[100];

    struct    sockaddr_in fsin;
    struct    sockaddr_in Sin;

unsigned int __stdcall Chat(PVOID PM) 
{    
        char buf1[2000];
        char buf2[2000];
        char buf3[2000];
        char buf4[2000];
        (void) time(&now);
        pts = ctime(&now);
        sockets[number] = ssock;
        SOCKET    sock = ssock;
        ThreadID[number] = threadID;
        unsigned int threadid = threadID;
        sprintf(buf1,"系统： %s你已经进入聊天室了!\n",pts,threadid);
        (void) send(sock,buf1, sizeof(buf1), 0); 
		size++;
		//printf("----------IP:%s 端口:%d----------\n",
		//	inet_ntoa(fsin.sin_addr),fsin.sin_port);
      /*  sprintf(buf2," 线程号 <%d> 客户<>  enter  \n",threadid);//进入聊天室
        printf("%s ",buf2);     */   
       // printf("\t将自动把此数据发送给所有客户！ \n");
       /* for(int i=0;i<=number;i++)
        {            
            if(sockets[i] != NULL && sockets[i] != sock)
            {
            (void) send(sockets[i],buf2, sizeof(buf2), 0); 
            printf(" 发送至线程号<%d>成功！\n",ThreadID[i]);
            }
        }
        printf(" \n");*/


flag1:cc = recv(sock, buf3, BUFLEN, 0);   //cc为接收的字符数
    if(cc == SOCKET_ERROR|| cc == 0)
    {
       // (void) time(&now);
       // pts = ctime(&now);
      //  sprintf( buf3," 线程号 <%d> 客户<IP:%s 端口:%d>  leave !  \n \t\t时间： %s",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,pts);
        sock = NULL;    
        sockets[number] = NULL;
        CloseHandle(hThread[number]);
       // printf("%s ", buf3);        
       // printf("\t将自动把此数据发送给所有客户！ \n");
       /* for(int i=0;i<=number;i++)
        {            
            if(sockets[i] != NULL && sockets[i] != sock)
            {
            (void) send(sockets[i], buf3, sizeof(buf3), 0);     
            printf(" 发送至线程号<%d>成功！\n",ThreadID[i]);
            }            
        }
    printf(" \n");*/
    }

    else if(cc > 0) 
    {
        (void) time(&now);
        pts = ctime(&now);
		printf("----------IP:%s 端口:%d----------\n",
			inet_ntoa(fsin.sin_addr),fsin.sin_port);
		//sprintf(buf4," 线程号 <%d> 客户<IP:%s 端口:%d>说 ：%s  \n \t\t时间 ： %s",
		//	threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,buf3,pts);
        printf("%s ",buf3);
        //printf("\t将自动把此数据发送给所有客户！ \n");
        for(int i=0;i<=number;i++)
        {            
            if(sockets[i] != NULL && sockets[i] != sock)
            {
            (void) send(sockets[i],buf3, sizeof(buf3), 0);         
           // printf(" 发送至线程号<%d>成功！\n",ThreadID[i]);
            }            
        }
        printf("\n在线%d人\n",size);

        goto flag1;
    }
        (void) closesocket(sock);
    
        return 0;
        }


/*------------------------------------------------------------------------
 * main - Iterative TCP server for DAYTIME service
 *------------------------------------------------------------------------
 */
void main(int argc, char *argv[]) 
/* argc: 命令行参数个数， 例如：C:\> TCPdaytimed 8080 
                     argc=2 argv[0]="TCPdaytimed",argv[1]="8080" */
{
    int     alen;                    /* from-address length               */    
    WSADATA wsadata; 
    char    *service = "5050";    
    WSAStartup(WSVERS, &wsadata);                         
    msock = socket(PF_INET, SOCK_STREAM, 0);              
    memset(&Sin, 0, sizeof(Sin));
    Sin.sin_family = AF_INET;
    Sin.sin_addr.s_addr = INADDR_ANY;                    
    Sin.sin_port = htons((u_short)atoi(service));        
    bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));   
    listen(msock, 5);                                    

    printf("\t\t\t\t猪琦琦聊天室\n");
        number = -1;
    while(1)                                    
    {                
        alen = sizeof(struct sockaddr);
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
        number ++;
        hThread[number] = (HANDLE)_beginthreadex(NULL, 0,Chat,NULL, 0, &threadID);        
    }
    (void) closesocket(msock);
    WSACleanup();                         
}