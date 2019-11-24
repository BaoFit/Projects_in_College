// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "csocketclient.h"
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySocket

CMySocket::CMySocket()
{
	memset(m_szBuffer,0,sizeof(m_szBuffer));
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//获取socket数据  
    Receive(m_szBuffer,sizeof(m_szBuffer)); 
	((CChat*)pDlg)->OnRecieve(m_szBuffer);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CAsyncSocket::OnSend(nErrorCode);
}

void CMySocket::SetParentDlg(CDialog * p)
{
	pDlg=p;
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMySocket member functions


/*



int CMySocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CSocket::Send(lpBuf, nBufLen, nFlags);
}

int CMySocket::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}*/
