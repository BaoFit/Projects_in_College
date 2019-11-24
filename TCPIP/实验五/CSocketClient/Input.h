#include "MyClienct.h"
#if !defined(AFX_INPUT_H__C8CC63D8_FDB8_4827_B5F6_83CF16757FDB__INCLUDED_)
#define AFX_INPUT_H__C8CC63D8_FDB8_4827_B5F6_83CF16757FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Input.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInput dialog

class CInput : public CDialog
{
// Construction
public:
	CInput(CWnd* pParent = NULL);  
	void ChuanDi(CMyClienct *cli,CString id); // standard constructor

// Dialog Data
	//{{AFX_DATA(CInput)
	enum { IDD = IDD_DIALOG1 };
	CString	m_login_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CMyClienct *cli;
	CString id;
	// Generated message map functions
	//{{AFX_MSG(CInput)
	afx_msg void OnChangeEdit3();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT_H__C8CC63D8_FDB8_4827_B5F6_83CF16757FDB__INCLUDED_)
