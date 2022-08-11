#if !defined(AFX_DLGINCHIOPTION_H__755E7DF9_6098_4C3D_A9EB_E209B8F1E5A7__INCLUDED_)
#define AFX_DLGINCHIOPTION_H__755E7DF9_6098_4C3D_A9EB_E209B8F1E5A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInchiOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInchiOption dialog

class CDlgInchiOption : public CDialog
{
// Construction
public:
	CDlgInchiOption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInchiOption)
	enum { IDD = IDD_INCHI_OPTIONS_DIALOG };
	int		m_RadioStereo;
	BOOL	m_CheckStereo;
	BOOL	m_IgnoreIso;
	BOOL	m_bMetal;
	BOOL	m_bTaut;
	BOOL	m_CheckNarrow;
	BOOL	m_bDisable;
	int		m_RadioPlain;
	BOOL	m_bTauto_1_5;
	BOOL	m_bSUU;
	BOOL	m_bSLUUD;
	//}}AFX_DATA

	void GetOptions(CStringArray& Opt) const;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInchiOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInchiOption)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStereo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINCHIOPTION_H__755E7DF9_6098_4C3D_A9EB_E209B8F1E5A7__INCLUDED_)
