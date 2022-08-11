#if !defined(AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_)
#define AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptions.h : header file
//

#include "DlgIchiOption.h"

class BrowseFileEdit : public SECBrowseFileEdit
{
private:
	BOOL m_bOpenDialog;
public:
	BrowseFileEdit() {m_bOpenDialog = TRUE;}
	virtual void OnBrowse();
	void SetType(BOOL bOpen) {m_bOpenDialog = bOpen;}

};
/////////////////////////////////////////////////////////////////////////////
// DlgOptions dialog

class DlgOptions : public CDialog
{
// Construction
public:
	DlgOptions(CWnd* pParent = NULL);   // standard constructor

	BrowseFileEdit m_editFileInput;
+	BOOL m_bMerge;
	CString m_OldInputFile;
	CDlgInchiOption m_Dlg;
	void GetOptions(CStringArray& Opt, int *Write2Disk ) const;

// Dialog Data
	//{{AFX_DATA(DlgOptions)
	enum { IDD = IDD_DIALOG1 };
	CString	m_InputFile;
	CString	m_Header;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONS_H__CC9B85F3_8E14_4F72_8223_2173249C1377__INCLUDED_)
