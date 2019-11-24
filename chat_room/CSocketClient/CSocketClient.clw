; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySocket
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "csocketclient.h"
LastPage=0

ClassCount=5
Class1=CChat
Class2=CCSocketClientApp
Class3=CAboutDlg
Class4=CCSocketClientDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_CSOCKETCLIENT_DIALOG
Class5=CMySocket
Resource3=IDD_DIALOG1

[CLS:CChat]
Type=0
BaseClass=CDialog
HeaderFile=Chat.h
ImplementationFile=Chat.cpp
LastObject=CChat
Filter=D
VirtualFilter=dWC

[CLS:CCSocketClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=CSocketClient.h
ImplementationFile=CSocketClient.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CSocketClientDlg.cpp
ImplementationFile=CSocketClientDlg.cpp

[CLS:CCSocketClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=CSocketClientDlg.h
ImplementationFile=CSocketClientDlg.cpp
LastObject=CCSocketClientDlg

[DLG:IDD_DIALOG1]
Type=1
Class=CChat
ControlCount=12
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_EDIT1,edit,1351682244
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_BUTTON3,button,1342242816
Control8=IDC_EDIT4,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT5,edit,1350633600
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CSOCKETCLIENT_DIALOG]
Type=1
Class=CCSocketClientDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_EDIT2,edit,1350631552

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CMySocket
VirtualFilter=uq

