// MyClienct.cpp: implementation of the CMyClienct class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CSocketClient.h"
#include "MyClienct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define DEFAULT_PORT 4499
#define DEFAULT_IP "192.168.43.206"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyClienct::CMyClienct()
{

}

CMyClienct::~CMyClienct()
{

}

void CMyClienct::link()
{
	int iPort=DEFAULT_PORT;
	char ip[]=DEFAULT_IP;
	memset(recv_buf,0,sizeof(recv_buf));
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("Failed to load Winsock.\n");
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
		printf("socket()Failed:%d\n",WSAGetLastError());
		return;
	}
	iLen=sizeof(ser);
}

void CMyClienct::send(CString s)
{
	strncpy(send_buf,(LPCTSTR)s,sizeof(send_buf));
	sendto(sClient,send_buf,sizeof(send_buf),0,(struct sockaddr*)&ser,iLen);
}

void CMyClienct::receive()
{
	recvfrom(sClient,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&ser,&iLen);
}

void CMyClienct::close_socket()
{
	closesocket(sClient);
	WSACleanup();
}
	
	