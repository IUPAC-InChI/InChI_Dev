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



/////////////////////////////////////////////////////////////////////////////
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
	m_bWriteToDisk = FALSE;
	m_bNPZZ = FALSE;
	m_bFoldCRU = FALSE;
	m_bNoFrameShift = FALSE;
	m_bPolymers = FALSE;
	m_bNoEdits = FALSE;
	m_bZzAsStar = TRUE;
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

/////////////////////////////////////////////////////////////////////////////
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
	DDX_Check(pDX, IDC_CHECK_WRITE_LOGS, m_bWriteToDisk );

	DDX_Check(pDX, IDC_CHECK_NPZZ, m_bNPZZ );
	DDX_Check(pDX, IDC_CHECK_TREAT_POLYMERS, m_bPolymers );
	DDX_Check(pDX, IDC_CHECK_FOLDCRU, m_bFoldCRU);
	DDX_Check(pDX, IDC_CHECK_NOEDITS, m_bNoEdits );
	DDX_Check(pDX, IDC_NO_FRAMESHIFT, m_bNoFrameShift );
	DDX_Check(pDX, IDC_CHECK_ZZ_AS_STAR, m_bZzAsStar );
	
		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInchiOption, CDialog)
	//{{AFX_MSG_MAP(CDlgInchiOption)
	ON_BN_CLICKED(IDC_CHECK_STEREO, OnCheckStereo)
	ON_BN_CLICKED(IDC_CHECK_FOLDCRU, OnCheckFoldCRU)
	ON_BN_CLICKED(IDC_NO_FRAMESHIFT, OnCheckNoFrameShift )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDlgInchiOption message handlers


/////////////////////////////////////////////////////////////////////////////
BOOL CDlgInchiOption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnCheckStereo();
	OnCheckFoldCRU();
	OnCheckNoFrameShift();
#ifdef STD_WINCHI
	GetDlgItem(IDC_CHECK_REC)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_TAUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_DISABLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_DISABLE)->EnableWindow(FALSE);
	DDX_Check(IDC_CHECK_TREAT_POLYMERS)->EnableWindow(FALSE);
#endif
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
void CDlgInchiOption::OnCheckFoldCRU()
{
	BOOL bChecked = IsDlgButtonChecked(IDC_NO_FRAMESHIFT) != 0;
	
	m_bNoEdits = !bChecked;
	GetDlgItem(IDC_CHECK_NOEDITS)->EnableWindow(!bChecked);

}

/////////////////////////////////////////////////////////////////////////////
void CDlgInchiOption::OnCheckNoFrameShift()
{
	BOOL bChecked = IsDlgButtonChecked(IDC_CHECK_FOLDCRU) != 0;
	
	m_bNoEdits = !bChecked;
	GetDlgItem(IDC_CHECK_NOEDITS)->EnableWindow(!bChecked);

}

/////////////////////////////////////////////////////////////////////////////
void CDlgInchiOption::GetOptions(CStringArray& Opt, int *Write2Disk ) const
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
	if ( m_bWriteToDisk )
	{
		*Write2Disk = 1;
	}
	else
	{
		*Write2Disk = 0;
	}




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
		//Opt.Add("/NoADP");

	if(m_bTauto_1_5)
	{
		Opt.Add("/15T");
	}
	
	if(m_bNPZZ)
	{
		Opt.Add("/NPZZ");
	}

	if (m_bFoldCRU)
	{
		Opt.Add("/FoldCRU");
	}

	if (m_bNoFrameShift)
	{
		Opt.Add("/NoFrameShift");
	}

	if(m_bPolymers)
	{
		Opt.Add("/Polymers");
	}

	if(m_bNoEdits)
	{
		Opt.Add("/NoEdits");
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
