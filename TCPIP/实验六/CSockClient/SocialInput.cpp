// SocialInput.cpp : implementation file
//

#include "stdafx.h"
#include "CSockClient.h"
#include "SocialInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocialInput dialog


CSocialInput::CSocialInput(CWnd* pParent /*=NULL*/)
	: CDialog(CSocialInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSocialInput)
	m_social_input = _T("");
	//}}AFX_DATA_INIT
}


void CSocialInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSocialInput)
	DDX_Text(pDX, IDC_EDIT1, m_social_input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSocialInput, CDialog)
	//{{AFX_MSG_MAP(CSocialInput)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocialInput message handlers

void CSocialInput::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_social_input);
}

void CSocialInput::ChuanDi2(CMyClient *cli,CString id) 
{
	this->cli=cli;
	this->id=id;
}

void CSocialInput::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(strcmp(m_social_input,"")==0)
		MessageBox("发送信息不能为空!");
	else
	{
		cli->sendValue("qunliao");
		cli->sendValue(id);
		cli->sendValue(m_social_input);
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	}
}

void CSocialInput::OnButton2() 
{
	// TODO: Add your control notification handler code here
		DestroyWindow();
}
