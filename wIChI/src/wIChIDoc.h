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


// wIChIDoc.h : interface of the CWINChIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINCHIDOC_H__69147FEC_F1C4_4D65_8D1E_CF58107323A2__INCLUDED_)
#define AFX_WINCHIDOC_H__69147FEC_F1C4_4D65_8D1E_CF58107323A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CWINChIView;
#include "DlgOptions.h"
#include "DlgGoTo.h"


extern BOOL gbThreadON;

class CWINChIDoc : public CDocument
{
protected: // create from serialization only
	CWINChIDoc();
	DECLARE_DYNCREATE(CWINChIDoc)

// Attributes
public:
//   DrawData * m_pDrawData;
    const DrawData * GetCurrentDrawData(AT_NUMB* nNewEquLabel = NULL);
	void RunExternalFile(const CString& fname, BOOL bMerge);
private:
    INChIParams * m_pINChIParams;
    INChIParams * m_pINChIBatchParams;
	DlgOptions m_Dlg;
	CDlgGoTo m_GoToDlg;
	CString m_OutputFile, m_LogFile, m_ProblemFile;
	BOOL m_bTautomer, m_bMetal, m_bKeepComponent, m_bCompSelected;
	BOOL m_bWriteToDisk;
	BOOL m_bNPZZ;
	BOOL m_bPolymers;
	BOOL m_bFoldCRU;
	BOOL m_bNoFrameShift;
	BOOL m_bNoPolymerEdits;
	BOOL m_bZzAsStar;
	const DrawData * GetDrawData(int nComp, int nRadio, BOOL bTaut, BOOL bMet);
	BOOL IsRadioEnable(int nRadioID);
	void GetStructure();
	void JustReadStructure();
	void GetOffsetStructure(int offset);
	void MoveToRecord(int nrecord);
	void InitCtrls();
	void ResetCtrls();
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWINChIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWINChIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
   void FreeINChI();
   void FreeBatchINChI();
   CWINChIView * GetWINChIView();
   CEditView * GetCEditView();
   void Clear();
   void UpdateWINChIView();
   void UpdateEditView();

   void ProcessInput(BOOL bBatch, int how = 0);
   

// Generated message map functions
protected:
	//{{AFX_MSG(CWINChIDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnViewNextStru();
	afx_msg void OnThreadFinished();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnViewCancel();
	afx_msg void OnUpdateViewCancel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNextStru(CCmdUI* pCmdUI);
	afx_msg void OnViewGotoStru();
	afx_msg void OnUpdateViewGotoStru(CCmdUI* pCmdUI);
	afx_msg void OnSelchangeComponents();
	afx_msg void OnRadio();
	afx_msg void OnFileProcessAll();
	afx_msg void OnUpdateFileProcessAll(CCmdUI* pCmdUI);
	afx_msg void OnEdtChange();
	afx_msg void OnUpdateComponents(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRadioOriginal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRadioPreprocessed(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnUpdateOptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnViewPrevStru();
	afx_msg void OnUpdateViewPrevStru(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRadioRes(CCmdUI* pCmdUI);
	afx_msg void OnCheckRec();
	afx_msg void OnCheckTaut();
	afx_msg void OnUpdateCheckRec(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckTaut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckNoEdits(CCmdUI* pCmdUI);
	afx_msg void OnCheckWriteLogs();
	afx_msg void OnCheckNoEdits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCHIDOC_H__69147FEC_F1C4_4D65_8D1E_CF58107323A2__INCLUDED_)
