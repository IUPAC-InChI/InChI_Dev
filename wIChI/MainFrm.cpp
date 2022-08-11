// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "wIChI.h"

#include "MainFrm.h"
#include "wIChIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void  SetStatusText(LPCSTR Str)
{
	CWnd * pWnd = AfxGetMainWnd();
	if( pWnd && ::IsWindow( pWnd->GetSafeHwnd() ) )
		pWnd->SendMessage( WM_APP + 1, 0, (LPARAM) Str );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_MESSAGE(WM_APP + 1, OnDisplayStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if( !m_wndDlgBar.Create(this,IDD_DIALOGBAR,CBRS_TOP|CBRS_TOOLTIPS,AFX_IDW_CONTROLBAR_FIRST ) )
	{
      TRACE0("Failed to create DlgBar\n");
      return -1;      // Fail to create.
    }

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *)m_wndDlgBar.GetDlgItem(IDC_SPIN1);
	pSpin->SetBuddy(m_wndDlgBar.GetDlgItem(IDC_EDIT_SPIN));
	pSpin->SetRange(0,0);
	m_wndDlgBar.CheckDlgButton(IDC_CHECK_TAUT,1);

   
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}



	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);
#ifdef STD_WINCHI
	SetTitle(_T("stdwInChI-1"));
#else
	SetTitle(_T("winchi-1"));
#endif

	return 0;
}

CFont Font;

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	if( !m_wndSplitter.CreateStatic( this, 2, 1) )
		return FALSE;
	if( !m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CWINChIView), CSize(100,2*rect.Height()/3), pContext) )
		return FALSE;
	if( !m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CTextView), CSize(100,100), pContext) )
		return FALSE;

	LOGFONT MyLogFont;
    memset( &MyLogFont, 0, sizeof( LOGFONT ) );
    MyLogFont.lfHeight = -MulDiv(9, GetDC()->GetDeviceCaps(LOGPIXELSY), 72);
	MyLogFont.lfWeight = FW_NORMAL; 
    strncpy( MyLogFont.lfFaceName, "Arial", LF_FACESIZE );
	Font.CreateFontIndirect( &MyLogFont ); 
	CEditView * pEditView = (CEditView *) m_wndSplitter.GetPane(1,0);
	pEditView->SetFont(&Font);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
LRESULT CMainFrame::OnDisplayStatus(WPARAM wParam, LPARAM lParam)
{
// AFX_IDS_IDLEMESSAGE
	m_wndStatusBar.SetPaneText( 0, LPCTSTR( lParam ) );
	return 0;

}

void CMainFrame::ResetCtrls()
{
	((CComboBox *) m_wndDlgBar.GetDlgItem(ID_COMPONENTS))->ResetContent();
	SetRangeAndPos(0,0);
	m_wndDlgBar.CheckRadioButton(IDC_RADIO_ORIGINAL,IDC_RADIO_RES,0);
	m_wndDlgBar.GetDlgItem(IDC_STATIC_RESULTS)->SetWindowText("Result");
}

BOOL CMainFrame::GetCtrlState( int& nComp, int& nRadio, int& nSet, BOOL& bTaut, BOOL& bMet, BOOL& bOriginal)
{
	CComboBox *pCombo = (CComboBox *)m_wndDlgBar.GetDlgItem(ID_COMPONENTS);
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *)m_wndDlgBar.GetDlgItem(IDC_SPIN1);
	nComp = pCombo->GetCurSel();
	bOriginal = 0 == nComp;
	if( nComp != CB_ERR )
		nComp = pCombo->GetItemData(nComp);
	bTaut = m_wndDlgBar.IsDlgButtonChecked(IDC_CHECK_TAUT) ? 1 : 0;
	bMet = m_wndDlgBar.IsDlgButtonChecked(IDC_CHECK_REC) ? 1 : 0;
	nRadio = m_wndDlgBar.GetCheckedRadioButton(IDC_RADIO_ORIGINAL, IDC_RADIO_RES);
	nSet = pSpin->GetPos();
	return nComp != CB_ERR;
}

void CMainFrame::SetComboFocus()
{
	m_wndDlgBar.GetDlgItem(ID_COMPONENTS)->SetFocus();
}

void CMainFrame::CheckRadio(UINT nID)
{
	m_wndDlgBar.CheckRadioButton(IDC_RADIO_ORIGINAL,IDC_RADIO_RES,nID);
}

void CMainFrame::SetRangeAndPos(int max, int pos )
{
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *)m_wndDlgBar.GetDlgItem(IDC_SPIN1);
	pSpin->SetRange(0,max);
	pSpin->SetPos(pos);
	CWnd * pStat = m_wndDlgBar.GetDlgItem(IDC_STATIC_NSETS);
	if( max == 0) 
		pStat->SetWindowText("No sets of");
	else
	{
		CString Str = "1 set of";
		if(max > 1 ) 
			Str.Format("%d sets of",max);
		pStat->SetWindowText(Str);
	}
}

void CMainFrame::InitCtrls(const CStringArray& ar, const CUIntArray& dat)
{
	CComboBox *pCombo = (CComboBox *)m_wndDlgBar.GetDlgItem(ID_COMPONENTS);
	ResetCtrls();
	int sz = ar.GetSize();
	if( sz )
	{
		if( sz == 1 )
		{
			m_wndDlgBar.GetDlgItem(IDC_STATIC_RESULTS)->SetWindowText("Result for one component");
			pCombo->AddString(ar[0]);
			pCombo->SetItemData(0,dat[0]);
		}
		else
		{
			CString str;
			str.Format("Results for %d components",sz-1);
			m_wndDlgBar.GetDlgItem(IDC_STATIC_RESULTS)->SetWindowText(str);
			for( int i = 0; i < sz; i++ )
			{
				pCombo->AddString(ar[i]);
				pCombo->SetItemData(i,dat[i]);
			}
		}
		pCombo->SetCurSel(0);
	}
}



