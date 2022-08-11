// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1E5F257B_DA33_41BF_8A03_AF9075A4F8BD__INCLUDED_)
#define AFX_MAINFRM_H__1E5F257B_DA33_41BF_8A03_AF9075A4F8BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextView.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CStatusBar  m_wndStatusBar;
	

	void ResetCtrls();
	BOOL GetCtrlState( int& nComp, int& nRadio, int& nSet, BOOL& bTaut, BOOL& bMet, BOOL& bOriginal);
	void SetComboFocus();
	void CheckRadio(UINT nID);
	void SetRangeAndPos(int max, int pos );
	void InitCtrls(const CStringArray& str, const CUIntArray& dat);

protected:  // control bar embedded members
	CDialogBar  m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnDisplayStatus(WPARAM wParam, LPARAM lParam);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void SetStatusText( LPCSTR text );

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1E5F257B_DA33_41BF_8A03_AF9075A4F8BD__INCLUDED_)
