// MyClienct.cpp: implementation of the CMyClienct class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CSockClient.h"
#include "MyClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define DEFAULT_PORT 4490
#define DEFAULT_IP "192.168.1.100"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyClient::CMyClient()
{

}

CMyClient::~CMyClient()
{

}

void CMyClient::link()
{
	int iPort=DEFAULT_PORT;
	char ip[]=DEFAULT_IP;
	memset(recv_buf,0,sizeof(recv_buf));
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		MessageBox(NULL,"Failed to load Winsock", NULL, MB_OK);
		return;
	}
	//建立服务器端地址
	ser.sin_family=AF_INET;
	ser.sin_port=htons(iPort);
	ser.sin_addr.s_addr=inet_addr(ip);
    //建立客户端数据报套接口
	sClient=socket(AF_INET,SOCK_DGRAM,0);
	if(sClient==INVALID_SOCKET)
	{
		MessageBox(NULL,"Failed to socket", NULL, MB_OK);
	}
	iLen=sizeof(ser);
	
	connect(sClient,(struct sockaddr*)&ser,sizeof(ser));
}

void CMyClient::sendValue(CString s)
{
	strncpy(send_buf,(LPCTSTR)s,sizeof(send_buf));
	send(sClient,send_buf,sizeof(send_buf),0);
}

void CMyClient::receive()
{
	recv(sClient,recv_buf,sizeof(recv_buf),0);
}

void CMyClient::close_socket()
{
	closesocket(sClient);
	WSACleanup();
}
	
	