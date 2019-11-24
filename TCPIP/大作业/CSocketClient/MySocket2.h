// MySocket2.h: interface for the CMySocket2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET2_H__3C807EE7_8065_470D_A120_F11E29F9EA4B__INCLUDED_)
#define AFX_MYSOCKET2_H__3C807EE7_8065_470D_A120_F11E29F9EA4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMySocket2
{
public:
	SOCKET sClient;
	char send_buf[1024],recv_buf[1024];
	CMySocket2();
	virtual ~CMySocket2();
	void sendValue(CString s);  
	void recvValue();
	void closeConnect();
protected:
	struct sockaddr_in ser,cli;
	WSADATA wsaData;
};

#endif // !defined(AFX_MYSOCKET2_H__3C807EE7_8065_470D_A120_F11E29F9EA4B__INCLUDED_)
