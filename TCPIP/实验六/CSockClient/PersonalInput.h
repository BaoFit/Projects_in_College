#include "MyClient.h"
#if !defined(AFX_PERSONALINPUT_H__6FB85DB3_ADB7_4FB1_952C_434E11129D4D__INCLUDED_)
#define AFX_PERSONALINPUT_H__6FB85DB3_ADB7_4FB1_952C_434E11129D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonalInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonalInput dialog

class CPersonalInput : public CDialog
{
// Construction
public:
	void ChuanDi3(CMyClient *cli,CString id);
	CPersonalInput(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CPersonalInput)
	enum { IDD = IDD_DIALOG3 };
	CListBox m_listBox;
	CString	m_siliao_duixiang;
	CString	m_personal_input;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonalInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyClient *cli;
	CString id;

	// Generated message map functions
	//{{AFX_MSG(CPersonalInput)
//	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnSelchangeList4();
	afx_msg void OnChangeSelWebEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSONALINPUT_H__6FB85DB3_ADB7_4FB1_952C_434E11129D4D__INCLUDED_)
