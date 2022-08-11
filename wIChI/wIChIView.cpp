// wIChIView.cpp : implementation of the CWINChIView class
//

#include "stdafx.h"
#include "wIChI.h"

#include "wIChIDoc.h"
#include "wIChIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void GetPrintArea( HDC dc,  CRect& PrintArea, 
				  float LeftMargin = 1.0F, float RightMargin = 1.0F, float TopMargin = 1.0F, float BottomMargin = 1.0 )
{
	int left, right, top, bottom;
	int offsetx, offsety, width, height;

	left = (int)LeftMargin*GetDeviceCaps(dc,LOGPIXELSX);
	right = (int)RightMargin*GetDeviceCaps(dc,LOGPIXELSX);
	top = (int)TopMargin*GetDeviceCaps(dc,LOGPIXELSY);
	bottom = (int)BottomMargin*GetDeviceCaps(dc,LOGPIXELSY);

	offsetx = GetDeviceCaps(dc,PHYSICALOFFSETX);
	offsety = GetDeviceCaps(dc,PHYSICALOFFSETY);

	PrintArea.left = __max( 0, left - offsetx );
	PrintArea.top = __max( 0, top - offsety );

	width = GetDeviceCaps(dc,PHYSICALWIDTH); 
	height = GetDeviceCaps(dc,PHYSICALHEIGHT); 

	PrintArea.right = width - right - offsetx;
	PrintArea.bottom = height - bottom - offsety;

	if( PrintArea.right < PrintArea.left )
		PrintArea.right = PrintArea.left;

	if( PrintArea.bottom < PrintArea.top )
		PrintArea.bottom = PrintArea.top;

	::DPtoLP(dc, (LPPOINT)&PrintArea, 2); 

	return;
}


/////////////////////////////////////////////////////////////////////////////
// CWINChIView

IMPLEMENT_DYNCREATE(CWINChIView, CView)

BEGIN_MESSAGE_MAP(CWINChIView, CView)
	//{{AFX_MSG_MAP(CWINChIView)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWINChIView construction/destruction


CWINChIView::CWINChIView()
{
	// TODO: add construction code here

}

CWINChIView::~CWINChIView()
{
}


BOOL CWINChIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWINChIView drawing

void CWINChIView::OnDraw(CDC* pDC)
{
	CWINChIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	RECT rc;
	GetClientRect(&rc);
	AT_NUMB nNewEquLabel;
	const DrawData * pDrawData = GetDocument()->GetCurrentDrawData(&nNewEquLabel);
	::CreateInputStructPicture( pDC->GetSafeHdc(), pDrawData ? pDrawData->pWindowData : NULL, &rc, 0, nNewEquLabel );

}

/////////////////////////////////////////////////////////////////////////////
// CWINChIView diagnostics

#ifdef _DEBUG
void CWINChIView::AssertValid() const
{
	CView::AssertValid();
}

void CWINChIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWINChIDoc* CWINChIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWINChIDoc)));
	return (CWINChIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWINChIView message handlers

BOOL CWINChIView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPrView printing

BOOL CWINChIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWINChIView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	CView::OnBeginPrinting(pDC, pInfo);
}

void CWINChIView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	CView::OnEndPrinting(pDC, pInfo);
}

void CWINChIView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect PrintRect;
	HDC dc = pDC->GetSafeHdc();

	::GetPrintArea( dc,  PrintRect); 
	::IntersectClipRect(dc,PrintRect.left,PrintRect.top, PrintRect.right,PrintRect.bottom );

	AT_NUMB nNewEquLabel;
	const DrawData * pDrawData = GetDocument()->GetCurrentDrawData(&nNewEquLabel);
	if( pDrawData == NULL )
		return;

	MY_WINDOW_DATA * pWindowData = DupWinData(pDrawData->pWindowData);
	if( pWindowData == NULL )
		return;

	::CreateInputStructPicture( dc, pWindowData, &PrintRect, 1, nNewEquLabel);

	FreeWinData(pWindowData);
	free(pWindowData);

}

void CWINChIView::OnContextMenu(CWnd* pWnd, CPoint point) 
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

int CWINChIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_DropTarget.Register( this );
	
	return 0;
}



BOOL CWINChIView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	TCHAR szFileName[_MAX_PATH +1];
	STGMEDIUM stg;
	FORMATETC fmtetc = { CF_HDROP, NULL, DVASPECT_CONTENT, NULL,  TYMED_HGLOBAL };
	BOOL ret = FALSE;
	
	if( pDataObject->GetData( CF_HDROP, &stg, &fmtetc ) )
	{
		HDROP hdrop= (HDROP) GlobalLock(stg.hGlobal);
		if( NULL != hdrop )
		{
			UINT nFiles = DragQueryFile(hdrop,(UINT)-1,NULL,0);
			if( nFiles > 0 )
			{
				ZeroMemory(szFileName,_MAX_PATH +1);
				DragQueryFile(hdrop,0,(LPTSTR)szFileName,_MAX_PATH +1);
				GetDocument()->RunExternalFile(szFileName, FALSE);
				//
			}
			GlobalUnlock(hdrop);
			ret = TRUE;
		}
	}
	return ret;
	
//	return CView::OnDrop(pDataObject, dropEffect, point);
}

DROPEFFECT CWINChIView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
//	return CView::OnDragOver(pDataObject, dwKeyState, point);
	STGMEDIUM stg;
	FORMATETC fmtetc = { CF_HDROP, NULL, DVASPECT_CONTENT, NULL,  TYMED_HGLOBAL };
	if( pDataObject->GetData( CF_HDROP, &stg, &fmtetc ) )
	{
		HDROP hdrop= (HDROP) GlobalLock(stg.hGlobal);
		if( NULL != hdrop )
		{
			UINT nFiles = DragQueryFile(hdrop,(UINT)-1,NULL,0);
			GlobalUnlock(hdrop);
			if( nFiles > 0 )
				return 	DROPEFFECT_COPY;
		}
	}
	return DROPEFFECT_NONE;
}
