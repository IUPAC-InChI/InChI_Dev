#if !defined(AFX_BAR_H__DBF33D88_6624_4BF8_8861_3B21A1546CF8__INCLUDED_)
#define AFX_BAR_H__DBF33D88_6624_4BF8_8861_3B21A1546CF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Bar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Bar dialog

class Bar : public CDialogBar
{
// Construction
public:
	Bar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(Bar)
	enum { IDD = IDD_DIALOGBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Bar)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BAR_H__DBF33D88_6624_4BF8_8861_3B21A1546CF8__INCLUDED_)
