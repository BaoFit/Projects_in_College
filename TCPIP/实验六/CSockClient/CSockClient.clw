; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPersonalInput
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CSockClient.h"

ClassCount=7
Class1=CCSockClientApp
Class2=CCSockClientDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG2
Class4=CSocialInput
Resource4=IDD_DIALOG1
Class5=CSelect
Resource5=IDD_CSOCKCLIENT_DIALOG
Class6=CPersonalInput
Class7=niaho
Resource6=IDD_DIALOG3

[CLS:CCSockClientApp]
Type=0
HeaderFile=CSockClient.h
ImplementationFile=CSockClient.cpp
Filter=N

[CLS:CCSockClientDlg]
Type=0
HeaderFile=CSockClientDlg.h
ImplementationFile=CSockClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CCSockClientDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=CSockClientDlg.h
ImplementationFile=CSockClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CSOCKCLIENT_DIALOG]
Type=1
Class=CCSockClientDlg
ControlCount=6
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=CSocialInput
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816

[CLS:CSocialInput]
Type=0
HeaderFile=SocialInput.h
ImplementationFile=SocialInput.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSocialInput

[DLG:IDD_DIALOG2]
Type=1
Class=CSelect
ControlCount=3
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_BUTTON3,button,1342242816

[CLS:CSelect]
Type=0
HeaderFile=Select.h
ImplementationFile=Select.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON3

[DLG:IDD_DIALOG3]
Type=1
Class=CPersonalInput
ControlCount=8
Control1=IDC_LIST4,listbox,1352728833
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SEL_WEB_EDIT,edit,1350633600
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_BUTTON2,button,1342242816
Control8=IDC_BUTTON3,button,1342242816

[CLS:CPersonalInput]
Type=0
HeaderFile=PersonalInput.h
ImplementationFile=PersonalInput.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

[CLS:niaho]
Type=0
HeaderFile=niaho.h
ImplementationFile=niaho.cpp
BaseClass=CAsyncSocket
Filter=N

