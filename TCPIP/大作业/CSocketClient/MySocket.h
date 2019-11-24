#if !defined(AFX_MYSOCKET_H__9A8A9283_032E_420C_9087_A44309AEC64C__INCLUDED_)
#define AFX_MYSOCKET_H__9A8A9283_032E_420C_9087_A44309AEC64C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//
#include "afxsock.h"

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target
class CMySocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	char m_szBuffer[1024];//ÏûÏ¢»º³åÇø
	CMySocket();
	virtual ~CMySocket();
	void SetParentDlg(CDialog *p);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CDialog * pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__9A8A9283_032E_420C_9087_A44309AEC64C__INCLUDED_)
