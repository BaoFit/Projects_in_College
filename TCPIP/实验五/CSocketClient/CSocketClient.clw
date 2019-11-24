; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInput
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CSocketClient.h"

ClassCount=4
Class1=CCSocketClientApp
Class2=CCSocketClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CSOCKETCLIENT_DIALOG
Class4=CInput
Resource4=IDD_DIALOG1

[CLS:CCSocketClientApp]
Type=0
HeaderFile=CSocketClient.h
ImplementationFile=CSocketClient.cpp
Filter=N

[CLS:CCSocketClientDlg]
Type=0
HeaderFile=CSocketClientDlg.h
ImplementationFile=CSocketClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=CSocketClientDlg.h
ImplementationFile=CSocketClientDlg.cpp
Filter=D

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
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_EDIT2,edit,1350631552

[DLG:IDD_DIALOG1]
Type=1
Class=CInput
ControlCount=4
Control1=IDC_EDIT3,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BUTTON3,button,1342242816
Control4=IDC_BUTTON4,button,1342242816

[CLS:CInput]
Type=0
HeaderFile=Input.h
ImplementationFile=Input.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

