// Select.cpp : implementation file
//

#include "stdafx.h"
#include "CSockClient.h"
#include "Select.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define END "End_Link"
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelect dialog


CSelect::CSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelect, CDialog)
	//{{AFX_MSG_MAP(CSelect)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelect message handlers

void CSelect::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CSocialInput *dlg1=new CSocialInput();  
	if(dlg1)
	{
		dlg1->Create(IDD_DIALOG1,this); 
	}//第一个参数是对话框ID号
	dlg1->ShowWindow(SW_SHOW); 
	dlg1->ChuanDi2(cli,id);
}

void CSelect::OnButton2() 
{
	// TODO: Add your control notification handler code here; 
	CPersonalInput *dlg2=new CPersonalInput;
	if(dlg2)
	{
		dlg2->Create(IDD_DIALOG3,this); 
	}
	dlg2->ShowWindow(SW_SHOW); 
	dlg2->ChuanDi3(cli,id);
}

void CSelect::OnButton3() 
{
	// TODO: Add your control notification handler code here
	cli->sendValue(END);
	cli->sendValue(id);
	cli->close_socket();
	DestroyWindow();
}

void CSelect::ChuanDi1(CMyClient *cli,CString id) 
{
	this->cli=cli;
	this->id=id;	
}
