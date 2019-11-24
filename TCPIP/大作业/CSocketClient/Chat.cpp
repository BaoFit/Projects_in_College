// Chat.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketClient.h"
#include "Chat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChat dialog


CChat::CChat(CWnd* pParent /*=NULL*/)
	: CDialog(CChat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChat)
	m_sendValue = _T("");
	m_siliaoMember = _T("");
	//}}AFX_DATA_INIT
}


void CChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChat)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Text(pDX, IDC_EDIT3, m_sendValue);
	DDX_Text(pDX, IDC_EDIT4, m_siliaoMember);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChat, CDialog)
	//{{AFX_MSG_MAP(CChat)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChat message handlers

void CChat::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//聊天内容显示对话框
}

void CChat::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	//显示在线成员
	CString strText;   
    int nCurSel;        
    nCurSel = m_listBox.GetCurSel();           // 获取当前选中列表项   
    m_listBox.GetText(nCurSel, strText);       // 获取选中列表项的字符串   
    SetDlgItemText(IDC_EDIT4, strText); // 将选中列表项的字符串显示到编辑框中
}

void CChat::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//输入发送信息的内容
	GetDlgItem(IDC_EDIT3)->GetWindowText(m_sendValue);
}

void CChat::OnChangeEdit5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//显示在线人数
}

void CChat::OnChangeEdit4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//显示私聊对象
	GetDlgItem(IDC_EDIT4)->GetWindowText(m_siliaoMember);
}

void CChat::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//群聊
	char *pts;
	if(strcmp(m_sendValue,"")==0)
		MessageBox("发送信息不能为空!");
	else
	{
		time_t    now;
		(void) time(&now);
		pts = ctime(&now);
		sprintf(send_buf,"4@%s %s [群聊] %s\n",(LPCTSTR)id,pts,(LPCTSTR)m_sendValue);
		mysocket.Send(send_buf,sizeof(send_buf));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
	}
}

void CChat::OnButton2() 
{
	// TODO: Add your control notification handler code here
	//私聊
	char *pts;
	if(m_siliaoMember=="" || m_siliaoMember=="Empty")
		MessageBox("当前所选对象无法进行私聊，请刷新!");
	else if(strcmp(m_sendValue,"")==0)
		MessageBox("发送信息不能为空!");
	else
	{
		time_t    now;
		(void) time(&now);
		pts = ctime(&now);
		sprintf(send_buf,"5@%s@%s %s [私聊%s] %s\n",(LPCTSTR)m_siliaoMember,(LPCTSTR)id,pts,(LPCTSTR)m_siliaoMember,(LPCTSTR)m_sendValue);
		mysocket.Send(send_buf,sizeof(send_buf));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
	}
}

void CChat::OnButton3() 
{
	// TODO: Add your control notification handler code here
	//退出
	sprintf(send_buf,"6@%s",(LPCTSTR)id);
	mysocket.Send(send_buf,sizeof(send_buf));
	mysocket.Close();
	DestroyWindow();
}

void CChat::init(CString id)
{
	this->id=id;
	memset(recv_buf,0,sizeof(recv_buf));
	mysocket.Create();
	mysocket.SetParentDlg(this);
	mysocket.Connect("192.168.43.241",5050);
	mysocket.Send("3",sizeof("3"));
}

void CChat::OnRecieve(char *str)
{
	if(str[0]=='@')
	{
		int i,n;
		for(i=1;i<strlen(str);i++)
			if(str[i]=='@') break;
		str[i]='\0';
		memset(num,0,sizeof(num));
		strncpy(num,str+1,i-1);
		GetDlgItem(IDC_EDIT5)->SetWindowText(_T(num));
		for(int j=0;j<atoi(num)-1;j++)
		{
			i++;n=i;
			while(str[i]!='@')
			{
				i++;
			}
			str[i]='\0';
			strncpy(recv_buf,str+n,i-n);
			m_listBox.AddString(_T(recv_buf));
		}
		strcpy(recv_buf,str+i+1);
		m_listBox.AddString(_T(recv_buf));
	}
	else if(str[0]=='#')
	{
		mysocket.Send("3",sizeof("3"));
	}
	else
	{
		int nLength=m_edit1.SendMessage(WM_GETTEXTLENGTH);
		m_edit1.SetSel(nLength, nLength);
		m_edit1.ReplaceSel(str);
	}
}
