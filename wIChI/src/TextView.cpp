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



// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "wIChI.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CEditView)

/////////////////////////////////////////////////////////////////////////////
CTextView::CTextView()
{
}

/////////////////////////////////////////////////////////////////////////////
CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CEditView)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

/////////////////////////////////////////////////////////////////////////////
CWINChIDoc* CTextView::GetDocument()
{
	return (CWINChIDoc*) m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::OnDraw(CDC* pDC)
{
	// TODO: add draw code here
}


/////////////////////////////////////////////////////////////////////////////
BOOL CTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
    cs.style |= ES_READONLY;
	return bPreCreated;
}



/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
/////////////////////////////////////////////////////////////////////////////
void CTextView::AssertValid() const
{
	CEditView::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers
/////////////////////////////////////////////////////////////////////////////

// CPrView printing

/////////////////////////////////////////////////////////////////////////////
BOOL CTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_WINCHI_MENU));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	if( point.x == -1 && point.y == -1 ) // from keyboard
	{
		ClientToScreen(&point);
	}
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
	
}

/////////////////////////////////////////////////////////////////////////////
void CTextView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);	
}
