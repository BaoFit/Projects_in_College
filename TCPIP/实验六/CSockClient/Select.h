#include "SocialInput.h"
#if !defined(AFX_SELECT_H__243B17CF_1557_4FD3_B949_EC80AF90628C__INCLUDED_)
#define AFX_SELECT_H__243B17CF_1557_4FD3_B949_EC80AF90628C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Select.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelect dialog

class CSelect : public CDialog
{
// Construction
public:
	CSelect(CWnd* pParent = NULL);   // standard constructor
	void ChuanDi1(CMyClient *cli,CString id);
// Dialog Data
	//{{AFX_DATA(CSelect)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyClient *cli;
	CString id;

	// Generated message map functions
	//{{AFX_MSG(CSelect)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECT_H__243B17CF_1557_4FD3_B949_EC80AF90628C__INCLUDED_)
