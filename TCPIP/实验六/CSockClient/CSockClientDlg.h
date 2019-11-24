// CSockClientDlg.h : header file
//

#if !defined(AFX_CSOCKCLIENTDLG_H__78CA3522_02E7_41A5_8AC5_29E989C7D354__INCLUDED_)
#define AFX_CSOCKCLIENTDLG_H__78CA3522_02E7_41A5_8AC5_29E989C7D354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCSockClientDlg dialog

class CCSockClientDlg : public CDialog
{
// Construction
public:
	CCSockClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCSockClientDlg)
	enum { IDD = IDD_CSOCKCLIENT_DIALOG };
	CString	m_login_ID;
	CString	m_login_psw;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSockClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCSockClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKCLIENTDLG_H__78CA3522_02E7_41A5_8AC5_29E989C7D354__INCLUDED_)
