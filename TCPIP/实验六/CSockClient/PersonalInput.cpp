// PersonalInput.cpp : implementation file
//

#include "stdafx.h"
#include "CSockClient.h"
#include "PersonalInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonalInput dialog


CPersonalInput::CPersonalInput(CWnd* pParent /*=NULL*/)
	: CDialog(CPersonalInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPersonalInput)
	m_siliao_duixiang = _T("");
	m_personal_input = _T("");
	//}}AFX_DATA_INIT
}


void CPersonalInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPersonalInput)
	DDX_Text(pDX, IDC_SEL_WEB_EDIT, m_siliao_duixiang);
	DDX_Text(pDX, IDC_EDIT2, m_personal_input);
	DDX_Control(pDX, IDC_LIST4, m_listBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPersonalInput, CDialog)
	//{{AFX_MSG_MAP(CPersonalInput)
	//ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_LBN_SELCHANGE(IDC_LIST4, OnSelchangeList4)
	ON_EN_CHANGE(IDC_SEL_WEB_EDIT, OnChangeSelWebEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonalInput message handlers

void CPersonalInput::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_personal_input);
}

void CPersonalInput::OnButton1() 
{
	// TODO: Add your control notification handler code 
	if(m_siliao_duixiang=="" || m_siliao_duixiang=="Empty")
		MessageBox("当前所选对象无法进行私聊，请刷新!");
	else if(strcmp(m_personal_input,"")==0)
		MessageBox("发送信息不能为空!");
	else
	{
		cli->sendValue("siliao");
		cli->sendValue(id);
		cli->sendValue(m_siliao_duixiang);
		cli->sendValue(m_personal_input);
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
	}
}

void CPersonalInput::OnButton2() 
{
	// TODO: Add your control notification handler code here
	DestroyWindow();
}

void CPersonalInput::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_listBox.ResetContent();
	cli->sendValue("getOnMember");
	cli->receive();
	while(strcmp(cli->recv_buf,"end")!=0)
	{
		m_listBox.AddString(_T(cli->recv_buf));
		cli->receive();
	}
}

void CPersonalInput::ChuanDi3(CMyClient *cli,CString id) 
{
	this->cli=cli;
	this->id=id;
}
void CPersonalInput::OnSelchangeList4() 
{
	// TODO: Add your control notification handler code here
	CString strText;   
    int nCurSel;        
    nCurSel = m_listBox.GetCurSel();           // 获取当前选中列表项   
    m_listBox.GetText(nCurSel, strText);       // 获取选中列表项的字符串   
    SetDlgItemText(IDC_SEL_WEB_EDIT, strText); // 将选中列表项的字符串显示到编辑框中  
}

void CPersonalInput::OnChangeSelWebEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_SEL_WEB_EDIT)->GetWindowText(m_siliao_duixiang);
}
