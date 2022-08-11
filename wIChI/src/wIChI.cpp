/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.06
 * September 01, 2020
 *
 * The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST.
 * Modifications and additions by IUPAC and the InChI Trust.
 * Some portions of code were developed/changed by external contributors
 * (either contractor or volunteer) which are listed in the file
 * 'External-contributors' included in this distribution.
 *
 * IUPAC/InChI-Trust Licence No.1.0 for the
 * International Chemical Identifier (InChI)
 * Copyright (C) IUPAC and InChI Trust
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the IUPAC/InChI Trust InChI Licence No.1.0,
 * or any later version.
 *
 * Please note that this library is distributed WITHOUT ANY WARRANTIES
 * whatsoever, whether expressed or implied.
 * See the IUPAC/InChI-Trust InChI Licence No.1.0 for more details.
 *
 * You should have received a copy of the IUPAC/InChI Trust InChI
 * Licence No. 1.0 with this library; if not, please e-mail:
 *
 * info@inchi-trust.org
 *
 */



// wIChI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "wIChI.h"

#include "MainFrm.h"
#include "wIChIDoc.h"
#include "wIChIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CWINChIApp

BEGIN_MESSAGE_MAP(CWINChIApp, CWinApp)
	//{{AFX_MSG_MAP(CWINChIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWINChIApp construction


/////////////////////////////////////////////////////////////////////////////
CWINChIApp::CWINChIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CWINChIApp object

CWINChIApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CWINChIApp initialization
/////////////////////////////////////////////////////////////////////////////

BOOL CWINChIApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	::AfxOleInit();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWINChIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWINChIView));
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	CString Param;
	BOOL bMerge = FALSE;
	
	for (int i = 0; i < __argc; i++)
	{
		Param = __targv[i];
		Param.MakeUpper();
		if( Param == "/MERGE")
		{
			bMerge = TRUE;
			break;
		}
	}


	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH));
	LPTSTR slash = _tcsrchr(szBuff,'\\');
	ASSERT( slash != NULL );
	slash[1] = 0;  
	m_StartUpDir = szBuff;


	// The one and only window has been initialized, so show and update it.

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED); //^^^ SW_SHOW);
	m_pMainWnd->UpdateWindow();

	if( !cmdInfo.m_strFileName.IsEmpty() )
	{
		CWINChIDoc * pDoc; 
		POSITION pos = pDocTemplate->GetFirstDocPosition();
		if( pos && ( pDoc = (CWINChIDoc *)pDocTemplate->GetNextDoc(pos) ) )
			pDoc->RunExternalFile(cmdInfo.m_strFileName, bMerge);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
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
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
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


// App command to run the dialog
/////////////////////////////////////////////////////////////////////////////
void CWINChIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CWINChIApp message handlers

/////////////////////////////////////////////////////////////////////////////
int CWINChIApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	if( !gbThreadON  )
		::SetBitFree( &CG );
	
	return CWinApp::ExitInstance();
}
