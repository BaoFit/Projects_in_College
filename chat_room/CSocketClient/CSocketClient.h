// CSocketClient.h : main header file for the CSOCKETCLIENT application
//

#if !defined(AFX_CSOCKETCLIENT_H__85DB2C09_F7D6_4352_9228_0309326FC302__INCLUDED_)
#define AFX_CSOCKETCLIENT_H__85DB2C09_F7D6_4352_9228_0309326FC302__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCSocketClientApp:
// See CSocketClient.cpp for the implementation of this class
//

class CCSocketClientApp : public CWinApp
{
public:
	CCSocketClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocketClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCSocketClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKETCLIENT_H__85DB2C09_F7D6_4352_9228_0309326FC302__INCLUDED_)