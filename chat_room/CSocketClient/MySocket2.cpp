// MySocket2.cpp: implementation of the CMySocket2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CSocketClient.h"
#include "MySocket2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define DEFAULT_IP "192.168.43.241"
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySocket2::CMySocket2()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//MessageBox("WSAStartup()");
	}
	//创建流式套接字
	sClient=socket(AF_INET,SOCK_STREAM,0);
	if(sClient == INVALID_SOCKET)      
    {   
		//MessageBox("socket() Failed,Error=%d",WSAGetLastError()); 
    }       
	//绑定本地地址
	cli.sin_family=AF_INET;
	cli.sin_port=htons(5053);
	cli.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sClient,(sockaddr*)&cli,sizeof(cli))==SOCKET_ERROR)    
    {   
		//MessageBox("bind() Failed,Error=%d",WSAGetLastError());  
    } 
	memset(recv_buf,0,sizeof(recv_buf));
	//连接请求 
	ser.sin_family = AF_INET;
	ser.sin_port = htons(5050);
	ser.sin_addr.s_addr = inet_addr(DEFAULT_IP);
	connect(sClient, (sockaddr*)&ser, sizeof(ser));
}

CMySocket2::~CMySocket2()
{

}

void CMySocket2::sendValue(CString s)
{
	strncpy(send_buf,(LPCTSTR)s,sizeof(send_buf));
	send(sClient,send_buf,sizeof(send_buf),0);
}

void CMySocket2::recvValue()
{
	recv(sClient,recv_buf,sizeof(recv_buf),0);
}


void CMySocket2::closeConnect()
{
	closesocket(sClient);
	WSACleanup();
}