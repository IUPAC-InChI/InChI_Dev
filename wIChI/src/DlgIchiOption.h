/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.06
 * December 15, 2020
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
	BOOL	m_bWriteToDisk;
	BOOL	m_bNPZZ;
	BOOL	m_bPolymers;
	BOOL	m_bNoEdits;
	BOOL    m_bFoldCRU;
	BOOL    m_bNoFrameShift;
	BOOL	m_bZzAsStar;
	//}}AFX_DATA

	void GetOptions(CStringArray& Opt, int *Write2Disk ) const;

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
	afx_msg void OnCheckFoldCRU();
	afx_msg void OnCheckNoFrameShift();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINCHIOPTION_H__755E7DF9_6098_4C3D_A9EB_E209B8F1E5A7__INCLUDED_)
