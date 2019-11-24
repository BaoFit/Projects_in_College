// CSocketClientDlg.h : header file
//

#if !defined(AFX_CSOCKETCLIENTDLG_H__9FB626BA_79BD_412C_BFAA_F15C24AB490C__INCLUDED_)
#define AFX_CSOCKETCLIENTDLG_H__9FB626BA_79BD_412C_BFAA_F15C24AB490C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCSocketClientDlg dialog

class CCSocketClientDlg : public CDialog
{
// Construction
public:
	CCSocketClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCSocketClientDlg)
	enum { IDD = IDD_CSOCKETCLIENT_DIALOG };
	CString	m_id;
	CString	m_psw;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocketClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCSocketClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKETCLIENTDLG_H__9FB626BA_79BD_412C_BFAA_F15C24AB490C__INCLUDED_)
