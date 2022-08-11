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
	CString m_OutputFile, m_LogFile, m_ProblemFile;
	BOOL m_bTautomer, m_bMetal, m_bKeepComponent, m_bCompSelected;
	const DrawData * GetDrawData(int nComp, int nRadio, BOOL bTaut, BOOL bMet);
	BOOL IsRadioEnable(int nRadioID);
	void GetStructure();
	void GetOffsetStructure(int offset);
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINCHIDOC_H__69147FEC_F1C4_4D65_8D1E_CF58107323A2__INCLUDED_)
