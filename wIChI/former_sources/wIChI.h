// wIChI.h : main header file for the WICHI application
//

#if !defined(AFX_WINCHI_H__6C18DF78_0768_4C2C_B8AD_607D7BB026A8__INCLUDED_)
#define AFX_WINCHI_H__6C18DF78_0768_4C2C_B8AD_607D7BB026A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWINChIApp:
// See wIChI.cpp for the implementation of this class
//

class CWINChIApp : public CWinApp
{
public:
	CWINChIApp();
	CString m_StartUpDir;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWINChIApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWINChIApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCHI_H__6C18DF78_0768_4C2C_B8AD_607D7BB026A8__INCLUDED_)
