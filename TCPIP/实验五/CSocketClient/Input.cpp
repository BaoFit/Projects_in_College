// Input.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketClient.h"
#include "Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define END "End_Link"
#endif

/////////////////////////////////////////////////////////////////////////////
// CInput dialog


CInput::CInput(CWnd* pParent /*=NULL*/)
	: CDialog(CInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInput)
	m_login_input = _T("");
	//}}AFX_DATA_INIT
}


void CInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInput)
	DDX_Text(pDX, IDC_EDIT3, m_login_input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInput, CDialog)
	//{{AFX_MSG_MAP(CInput)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInput message handlers

void CInput::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT3)->GetWindowText(m_login_input);
}

void CInput::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if(strcmp(m_login_input,"")==0)
		MessageBox("发送信息不能为空!");
	else
	{
		cli->send(id);
		cli->send(m_login_input);
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
	}
}

void CInput::OnButton4() 
{
	// TODO: Add your control notification handler code here
	cli->send(id);
	cli->send(END);
	cli->close_socket();
	DestroyWindow();
}

void CInput::ChuanDi(CMyClienct *cli,CString id)
{
	this->cli=cli;
	this->id=id;
}
