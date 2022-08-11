// DlgInchiOption.cpp : implementation file
//

#include "stdafx.h"
#include "wIChI.h"
#include "DlgIchiOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInchiOption dialog


CDlgInchiOption::CDlgInchiOption(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInchiOption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInchiOption)
	m_RadioStereo = 0;
	m_CheckStereo = TRUE;
	m_IgnoreIso = FALSE;
	m_bMetal = TRUE;
	m_bTaut = FALSE;
	m_CheckNarrow = FALSE;
	m_bDisable = FALSE;
	m_RadioPlain = 0;
	m_bTauto_1_5 = FALSE;
	m_bSUU = FALSE;
	m_bSLUUD = FALSE;
	//}}AFX_DATA_INIT

#ifdef STD_WINCHI
	m_bTaut = TRUE;
	m_bMetal = FALSE;
#endif

#ifdef INCHI_VER_103
	m_bTaut = TRUE;
	m_bMetal = FALSE;
#endif

}


void CDlgInchiOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInchiOption)
	DDX_Radio(pDX, IDC_RADIO_ABS, m_RadioStereo);
	DDX_Check(pDX, IDC_CHECK_STEREO, m_CheckStereo);
	DDX_Check(pDX, IDC_CHECK_IGNORE_ISO, m_IgnoreIso);
	DDX_Check(pDX, IDC_CHECK_REC, m_bMetal);
	DDX_Check(pDX, IDC_CHECK_TAUT, m_bTaut);
	DDX_Check(pDX, IDC_CHECK_NARROW, m_CheckNarrow);
	DDX_Check(pDX, IDC_CHECK_DISABLE, m_bDisable);
	DDX_Radio(pDX, IDC_RADIO_PLAIN, m_RadioPlain);
	DDX_Check(pDX, IDC_CHECK_TAUTO_15, m_bTauto_1_5);
	DDX_Check(pDX, IDC_CHECK_SUU, m_bSUU);
	DDX_Check(pDX, IDC_CHECK_SLUUD, m_bSLUUD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInchiOption, CDialog)
	//{{AFX_MSG_MAP(CDlgInchiOption)
	ON_BN_CLICKED(IDC_CHECK_STEREO, OnCheckStereo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInchiOption message handlers

BOOL CDlgInchiOption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnCheckStereo();
#ifdef STD_WINCHI
	GetDlgItem(IDC_CHECK_REC)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_TAUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_DISABLE)->EnableWindow(FALSE);
#endif
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgInchiOption::OnCheckStereo() 
{
	// TODO: Add your control notification handler code here
	BOOL bChecked = IsDlgButtonChecked(IDC_CHECK_STEREO) != 0;
	BOOL bEnable = bChecked;
#ifdef STD_WINCHI
	bEnable = FALSE;
#endif
	GetDlgItem(IDC_RADIO_ABS)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_REL)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_REC)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_UCF)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_NARROW)->EnableWindow(bChecked);

	GetDlgItem(IDC_CHECK_SUU)->EnableWindow(bChecked);
	GetDlgItem(IDC_CHECK_SLUUD)->EnableWindow(bChecked);
}

void CDlgInchiOption::GetOptions(CStringArray& Opt) const
{

	if( m_CheckStereo )
	{
		switch(m_RadioStereo)
		{
		case 0:
#ifndef INCHI_VER_103
			Opt.Add("/S");
#endif
			break;
		case 1:
			Opt.Add("/SREL");
			break;
		case 2:
			Opt.Add("/SRAC");
			break;
		case 3:
			Opt.Add("/SUCF");
			break;
		}
	}
#ifdef INCHI_VER_103
	else
		Opt.Add("/SNon");
#endif
//	else //new
//		Opt.Add("/E");



	if( m_CheckNarrow )
	{
#ifndef INCHI_VER_103
		Opt.Add("/NEWPS");
#else
		Opt.Add("/NEWPSOFF");
#endif
	}

	if( m_bSUU )
	{
		Opt.Add("/SUU");
	}

	if( m_bSLUUD )
	{
		Opt.Add("/SLUUD");
	}

	if( m_bDisable ) // Keto-enol VER_103
		Opt.Add("/KET");
//		Opt.Add("/NoADP");

	if(m_bTauto_1_5)
	{
		Opt.Add("/15T");
	}

	switch(m_RadioPlain)
	{
	case 0:
		Opt.Add("/ANNPLAIN");
		break;
	case 1:
		Opt.Add("/ANNXML");
		break;
	}
/*	
	if( m_CheckComp )
	{
		Opt.Add("/ALT");
		Opt.Add("/SCT");
	}

	if(m_TimeOut)
	{
		CString str;
		str.Format("/W%d",m_TimeOut);
		Opt.Add(str);
	}
*/
	Opt.Add("/W120");
	Opt.Add(m_IgnoreIso ? "/CMPNONISO" : "/CMP");


}
