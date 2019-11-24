#include "PersonalInput.h"
#if !defined(AFX_SOCIALINPUT_H__067B75CB_87F7_4D36_839B_568E48FC06ED__INCLUDED_)
#define AFX_SOCIALINPUT_H__067B75CB_87F7_4D36_839B_568E48FC06ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SocialInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSocialInput dialog

class CSocialInput : public CDialog
{
// Construction
public:
	void ChuanDi2(CMyClient *cli,CString id);
	CSocialInput(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CSocialInput)
	enum { IDD = IDD_DIALOG1 };
	CString	m_social_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocialInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CMyClient *cli;
	CString id;
	// Generated message map functions
	//{{AFX_MSG(CSocialInput)
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCIALINPUT_H__067B75CB_87F7_4D36_839B_568E48FC06ED__INCLUDED_)
