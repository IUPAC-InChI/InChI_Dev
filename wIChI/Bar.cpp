// Bar.cpp : implementation file
//

#include "stdafx.h"
#include "wIChI.h"
#include "Bar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Bar dialog


Bar::Bar()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(Bar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



BEGIN_MESSAGE_MAP(Bar, CDialogBar)
	//{{AFX_MSG_MAP(Bar)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Bar message handlers

void Bar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogBar::OnKeyDown(nChar, nRepCnt, nFlags);
}

void Bar::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if( nChar == VK_UP  ||
		nChar == VK_DOWN )
	{
		return;
	}
	CDialogBar::OnKeyUp(nChar, nRepCnt, nFlags);
}
