// MyClient.h: interface for the CMyClienct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIENCT_H__AC85FBDD_12CC_4C52_91C3_E0333BB15693__INCLUDED_)
#define AFX_MYCLIENCT_H__AC85FBDD_12CC_4C52_91C3_E0333BB15693__INCLUDED_

#define DATA_BUFFER 1024

#if _MSC_VER > 1000
#pragma once
#pragma comment(lib,"ws2_32.lib")
#endif // _MSC_VER > 1000

class CMyClient  
{
protected:
	WSADATA wsaData;
	SOCKET sClient;
	struct sockaddr_in ser;
	int iLen;
	char send_buf[DATA_BUFFER];
public:
	char recv_buf[DATA_BUFFER];
	CMyClient();
	virtual ~CMyClient();
	void link();
	void sendValue(CString s);
	void receive();
	void close_socket();
};

#endif // !defined(AFX_MYCLIENCT_H__AC85FBDD_12CC_4C52_91C3_E0333BB15693__INCLUDED_)
