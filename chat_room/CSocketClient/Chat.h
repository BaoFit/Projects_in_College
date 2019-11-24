//#include <process.h>
#include "resource.h"
#include "MySocket.h"
#if !defined(AFX_CHAT_H__8841492D_0031_4597_BDA0_7EDA63F95EBA__INCLUDED_)
#define AFX_CHAT_H__8841492D_0031_4597_BDA0_7EDA63F95EBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Chat.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CChat dialog
//class CMySocket;
class CChat : public CDialog
{
// Construction
public:
	CString id;
	CChat(CWnd* pParent = NULL);   // standard constructor
	char num[1024],recv_buf[1024],send_buf[1024];
	void OnRecieve(char *buf);
	void OnClose();
	void init(CString id);
// Dialog Data
	//{{AFX_DATA(CChat)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_edit1;
	CEdit	m_edit5;
	CListBox	m_listBox;
	CString	m_sendValue;
	CString	m_siliaoMember;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMySocket mysocket;
	// Generated message map functions
	//{{AFX_MSG(CChat)
	afx_msg void OnButton1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnSelchangeList1();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit4();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAT_H__8841492D_0031_4597_BDA0_7EDA63F95EBA__INCLUDED_)
