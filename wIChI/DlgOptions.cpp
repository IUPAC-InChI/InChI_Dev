// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "wIChI.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BOOL HasTrailingSlash( const CString& str )
{
	int iLength = str.GetLength() - 1;

	if( str[iLength] == _T('\\') )
		return TRUE;

	return FALSE;
}


static BOOL IsDirectory( CString& str )
{
	//if it has a trailing slash...remove it...
	if( HasTrailingSlash(str) )
		str = str.Left(str.GetLength() - 1);

	// If the last character in the string is a : then
	// we are a root directory. CFile::GetStatus uses
	// FindFirstFile to verify our existence, and fails
	// on C:\ so we need to add some wildcards
	if(str.Right(1) == _T(":"))
	{
		str += _T("\\*.*");
	}

	//Get the status of the file...return TRUE if a directory...
	CFileStatus fs;
	if( CFile::GetStatus( str, fs ) && (fs.m_attribute & CFile::directory))
	{
		// GetStatus returns FALSE if it can't find the file
		// If it returns True, and it is a filename,
		// go to that directory instead of returning false
		return TRUE;
	}

	//otherwise return FALSE
	return FALSE;
}

void BrowseFileEdit::OnBrowse()
{
	CString str,strOrig;
	SECFileSystem fs;
	
	if( m_dwDialogStyle & OFN_NOCHANGEDIR )
		strOrig = fs.GetCurrentDirectory();

	if (m_strInitialFile.IsEmpty())
		GetWindowText(str);
	else
		str = m_strInitialFile; //they specified a file...assume valid...

	//Lets use an instance of SECFileSystem to check the validity of the text
	BOOL bClearStr = FALSE;

	//if string is empty...do nothing
	if( !str.IsEmpty() )
	{
		//check to see if it is a directory and not a file
		if( IsDirectory(str) )
		{
			//never can be too careful
			if( fs.DirectoryExists(str) )
			{
				fs.ChangeDirectory(str);
				bClearStr = TRUE;
			}
		}
		else //not a directory...
		{
			//if it is a file...we don't want to clear the string...
			//but if it isn't a file and it isn't a directory..probably bogus...clear it
			if( !fs.FileExists(str) )
				bClearStr = TRUE;
		}
	}
			
	
	if( bClearStr )
		str = _T("");

	CFileDialog Dialog(m_bOpenDialog, m_strExt, str, m_dwDialogStyle, m_strFilters, this);
	Dialog.m_ofn.lpstrTitle = GetBrowseCaption();
	
	if (Dialog.DoModal() == IDOK)
		SetWindowText(Dialog.GetPathName());

	if( m_dwDialogStyle & OFN_NOCHANGEDIR )
		fs.ChangeDirectory(strOrig);
}

/////////////////////////////////////////////////////////////////////////////
// DlgOptions dialog


DlgOptions::DlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOptions::IDD, pParent)
{
	m_bMerge = FALSE;
	//{{AFX_DATA_INIT(DlgOptions)
	m_InputFile = _T("");
	m_Header = _T("");
	//}}AFX_DATA_INIT
}

void DDV_EmptyString(CDataExchange* pDX, CString& Str, const CString& Message)
{
	if( pDX->m_bSaveAndValidate && Str.IsEmpty())
	{
		::AfxMessageBox(Message);
		pDX->Fail();
	}
}


void DlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOptions)
	DDX_Text(pDX, IDC_EDIT_INPUT_FILE, m_InputFile);
	DDV_EmptyString(pDX, m_InputFile, "Enter input file");
	DDX_Text(pDX, IDC_EDIT_SDFID, m_Header);
	//}}AFX_DATA_MAP

	if( !pDX->m_bSaveAndValidate )
	{
		m_OldInputFile = m_InputFile;
	}
	else
	{
		if( m_OldInputFile.CompareNoCase(m_InputFile) != 0 )
		{
			m_bMerge = FALSE;
		}
	}

}

BEGIN_MESSAGE_MAP(DlgOptions, CDialog)
	//{{AFX_MSG_MAP(DlgOptions)
	ON_BN_CLICKED(IDC_BUTTON_ADV, OnButtonAdv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOptions message handlers

BOOL DlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_editFileInput.Initialize(IDC_EDIT_INPUT_FILE, this);
	m_editFileInput.SetFileFilters("MolFile (*.mol)|*.mol|SDFile (*.sdf)|*.sdf|CMLFile (*.cml)|*.cml|All Files (*.*)|*.*||");
	m_editFileInput.ModifyDialogStyle(0,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgOptions::OnButtonAdv() 
{
	// TODO: Add your control notification handler code here
	m_Dlg.DoModal();
	
}

void DlgOptions::GetOptions(CStringArray& Opt) const
{
	CString str;
	char ext[_MAX_EXT];

   _splitpath( (LPCSTR)m_InputFile, NULL, NULL, NULL, ext );
   _strupr(ext);
    if( strcmp(ext,".CML") == 0 )
	{
		Opt.Add("/CML");
	}
	else
	{
		if( !m_Header.IsEmpty() ) 
		{
			str= "/SDF:";
			str += m_Header;
			Opt.Add(str);
		}
		else
			Opt.Add("/MOL");
	}

	if( m_bMerge )
		Opt.Add("/MERGE");

	m_Dlg.GetOptions(Opt);
}
