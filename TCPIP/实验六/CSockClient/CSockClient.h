// CSockClient.h : main header file for the CSOCKCLIENT application
//

#if !defined(AFX_CSOCKCLIENT_H__92C360F4_3ADF_400E_8B97_01BE505BFC52__INCLUDED_)
#define AFX_CSOCKCLIENT_H__92C360F4_3ADF_400E_8B97_01BE505BFC52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCSockClientApp:
// See CSockClient.cpp for the implementation of this class
//

class CCSockClientApp : public CWinApp
{
public:
	CCSockClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSockClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCSockClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKCLIENT_H__92C360F4_3ADF_400E_8B97_01BE505BFC52__INCLUDED_)
