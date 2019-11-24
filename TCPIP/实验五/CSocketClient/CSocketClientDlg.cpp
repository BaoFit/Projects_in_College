// CSocketClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketClient.h"
#include "CSocketClientDlg.h"
#include "Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSocketClientDlg dialog

CCSocketClientDlg::CCSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSocketClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSocketClientDlg)
	m_login_ID = _T("");
	m_login_psw = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSocketClientDlg)
	DDX_Text(pDX, IDC_EDIT1, m_login_ID);
	DDX_Text(pDX, IDC_EDIT2, m_login_psw);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCSocketClientDlg, CDialog)
	//{{AFX_MSG_MAP(CCSocketClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSocketClientDlg message handlers

BOOL CCSocketClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCSocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCSocketClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCSocketClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCSocketClientDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_login_ID);
}

void CCSocketClientDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_login_psw);
}

void CCSocketClientDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(strcmp(m_login_ID,"")==0)
		MessageBox("账号信息不能为空!");
	else if(strcmp(m_login_psw,"")==0)
		MessageBox("密码不能为空!");
	else
	{
		CMyClienct *cli1=new CMyClienct;
		cli1->link();
		cli1->send("denglu");
		cli1->send(m_login_ID);
		cli1->send(m_login_psw);
		cli1->receive();
		if(strcmp(cli1->recv_buf,"denglu_succeed")==0)
		{
			CInput *dlg=new CInput();
			dlg->Create(IDD_DIALOG1,this);    //第一个参数是对话框ID号
			dlg->ShowWindow(SW_SHOW); 
			dlg->ChuanDi(cli1,m_login_ID);
		}
		else if(strcmp(cli1->recv_buf,"psw_wrong")==0)
		{
			MessageBox("密码错误!");
			cli1->close_socket();
		}
		else if(strcmp(cli1->recv_buf,"ID_notexist")==0)
		{
			MessageBox("账号不存在!");
			cli1->close_socket();
		}
	}
}

void CCSocketClientDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if(strcmp(m_login_ID,"")==0)
		MessageBox("账号信息不能为空!");
	else if(strcmp(m_login_psw,"")==0)
		MessageBox("密码不能为空!");
	else
	{
		CMyClienct *cli=new CMyClienct;
		cli->link();
		cli->send("zhuce");
		cli->send(m_login_ID);
		cli->send(m_login_psw);
		cli->receive();
		if(strcmp(cli->recv_buf,"zhuce_succeed")==0)
			MessageBox("注册成功!");
		else if(strcmp(cli->recv_buf,"ID_exist")==0)
			MessageBox("账号已存在!");
		cli->close_socket();
	}
}
