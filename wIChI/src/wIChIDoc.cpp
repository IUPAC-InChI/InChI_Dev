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



// wIChIDoc.cpp : implementation of the CWINChIDoc class
//

#include "stdafx.h"
#include "wIChI.h"

#include "wIChIDoc.h"
#include "wIChIView.h"
#include "fthread.h"
#include "mainfrm.h"
#include "isis.h"


#include "../../INCHI-1-SRC/INCHI_BASE/src/ichitime.h"


#define MAX_NUM_COMP 1000

struct DrawDataAr
{
	int nComp;
	AT_NUMB * nSortedOrder;
	DRAW_DATA_AR v[MAX_NUM_COMP];
	void Clear();
	DrawDataAr() { nComp = 0;memset(v,0,sizeof(v));}
	~DrawDataAr() {Clear();}

};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL gbBatch = FALSE;
BOOL gbCanceled = FALSE;
BOOL gbThreadON = FALSE;
ThreadData gThreadData;

CString gResultOutput;



/////////////////////////////////////////////////////////////////////////////
void DrawDataAr::Clear()
{
	for( int i = 0; i <= nComp; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			if( v[i][j] )
			{
				FreeDrawData(v[i][j]);
				free(v[i][j]);
				v[i][j] = NULL;
			}
		}
	}
	nSortedOrder = NULL;
}

struct DrawDataAr gDrawingVec[2];

/////////////////////////////////////////////////////////////////////////////
void free_drawing_vec()
{
	for( int i = 0; i < 2; i++ )
	{
		gDrawingVec[i].Clear();
	}
}

/////////////////////////////////////////////////////////////////////////////
inline const struct DrawDataAr& get_current_draw_vec(int ind )
{
	int n = ind;
	if( n != 0 && gDrawingVec[1].nComp == 0)
		n = 0;
	return gDrawingVec[n];
}

/////////////////////////////////////////////////////////////////////////////
void draw_data_callback(DrawData * pDrawData)
{
		DrawData * v = (DrawData *)malloc(sizeof(DrawData));
		*v = *pDrawData;
		int ind = pDrawData->bReconnected ? 1 : 0;
		gDrawingVec[ind].v[pDrawData->nComponent][pDrawData->nType] = v;
}

/////////////////////////////////////////////////////////////////////////////
struct DrawData * get_draw_data_callback( int nComponent, int nType, int bReconnected )
{
	return gDrawingVec[bReconnected ? 1 : 0].v[nComponent][nType];
}


/////////////////////////////////////////////////////////////////////////////
int draw_data_exists_callback( int nComponent, int nType, int bReconnected )
{
	return get_draw_data_callback(nComponent, nType, bReconnected) != NULL;
}


/////////////////////////////////////////////////////////////////////////////
int thread_callback(int nCode)
{
	switch(nCode)
	{
	case THREAD_STARTED:
		 gbThreadON = TRUE;
		 break;
	case THREAD_FINISHED:
		 gbThreadON = FALSE;
		 AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_THREAD_FINISHED);
		 break;
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
void result_output(const char * format, va_list argptr )
{
	if( !gbBatch )
	{
		CString str;
		str.FormatV(format,argptr);
		str.Replace("\n","\r\n");
		gResultOutput += str;

		int tmp = 0;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
void push_result_string(const char *s )
{
	if( !gbBatch )
	{
		CString str(s);
		str.Replace("\n","\r\n");
		gResultOutput += str;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
int is_canceled( )
{
	return gbCanceled;
}


/////////////////////////////////////////////////////////////////////////////
// CWINChIDoc

IMPLEMENT_DYNCREATE(CWINChIDoc, CDocument)

BEGIN_MESSAGE_MAP(CWINChIDoc, CDocument)
	//{{AFX_MSG_MAP(CWINChIDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_VIEW_NEXT_STRU, OnViewNextStru)
	ON_COMMAND(ID_THREAD_FINISHED, OnThreadFinished)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_VIEW_CANCEL, OnViewCancel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CANCEL, OnUpdateViewCancel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEXT_STRU, OnUpdateViewNextStru)

	ON_COMMAND(ID_VIEW_GOTO_STRU, OnViewGotoStru)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GOTO_STRU, OnUpdateViewGotoStru)

	ON_CBN_SELCHANGE(ID_COMPONENTS, OnSelchangeComponents)
	ON_BN_CLICKED(IDC_RADIO_ORIGINAL, OnRadio)
	ON_COMMAND(ID_FILE_ALL, OnFileProcessAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_ALL, OnUpdateFileProcessAll)
	ON_EN_CHANGE(IDC_EDIT_SPIN,OnEdtChange)
	ON_UPDATE_COMMAND_UI(ID_COMPONENTS, OnUpdateComponents)
	ON_UPDATE_COMMAND_UI(IDC_RADIO_ORIGINAL, OnUpdateRadioOriginal)
	ON_UPDATE_COMMAND_UI(IDC_RADIO_PREPROCESSED, OnUpdateRadioPreprocessed)
	ON_COMMAND(ID_OPTIONS, OnOptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS, OnUpdateOptions)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_STRUCT, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTE_STRUCT, OnEditPaste)
	ON_COMMAND(ID_VIEW_PREV_STRU, OnViewPrevStru)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREV_STRU, OnUpdateViewPrevStru)
	ON_UPDATE_COMMAND_UI(IDC_RADIO_RES, OnUpdateRadioRes)
	ON_COMMAND(IDC_CHECK_REC, OnCheckRec)
	ON_COMMAND(IDC_CHECK_TAUT, OnCheckTaut)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_REC, OnUpdateCheckRec)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_TAUT, OnUpdateCheckTaut)

	ON_UPDATE_COMMAND_UI(IDC_CHECK_NOEDITS, OnUpdateCheckNoEdits)
	
	ON_BN_CLICKED(IDC_RADIO_RES, OnRadio)
	ON_BN_CLICKED(IDC_RADIO_PREPROCESSED, OnRadio)
	ON_BN_CLICKED(IDC_CHECK_REC, OnCheckRec)
	ON_BN_CLICKED(IDC_CHECK_WRITE_LOGS, OnCheckWriteLogs)

	ON_COMMAND(IDC_CHECK_NOEDITS, OnCheckNoEdits)
	ON_BN_CLICKED(IDC_CHECK_NOEDITS, OnCheckNoEdits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWINChIDoc construction/destruction

/////////////////////////////////////////////////////////////////////////////
CWINChIDoc::CWINChIDoc()
{
	m_pINChIParams = NULL;
	m_pINChIBatchParams = NULL;
	FWPRINT = result_output;
	FWPUSH = push_result_string;
	UserAction = is_canceled;
	DRAWDATA = draw_data_callback;
	DRAWDATA_EXISTS = draw_data_exists_callback;
	GET_DRAWDATA = get_draw_data_callback;
	m_bKeepComponent = m_bCompSelected = FALSE;
	m_bTautomer = m_bMetal = FALSE;
	m_bWriteToDisk = FALSE;
	m_bNPZZ = FALSE;
	m_bFoldCRU = FALSE;
	m_bNoFrameShift = FALSE;
	m_bPolymers = FALSE;
	m_bNoPolymerEdits = FALSE;
	m_bZzAsStar = TRUE;
	InitMDLClipBoard();

}

/////////////////////////////////////////////////////////////////////////////
CWINChIDoc::~CWINChIDoc()
{
	FreeINChI();
	::free_drawing_vec();
}

/////////////////////////////////////////////////////////////////////////////
BOOL CWINChIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWINChIDoc serialization

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}



/////////////////////////////////////////////////////////////////////////////
// CWINChIDoc diagnostics

#ifdef _DEBUG

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
CWINChIView * CWINChIDoc::GetWINChIView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf(RUNTIME_CLASS(CWINChIView)) )
		  return (CWINChIView *) pView;
	}   
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
CEditView * CWINChIDoc::GetCEditView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf(RUNTIME_CLASS(CEditView)) )
		  return (CEditView *) pView;
	}   
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::UpdateWINChIView()
{
	CView * pView = GetWINChIView();
	if( pView )
	{
		pView->Invalidate();
		pView->UpdateWindow();
	}
	SetTitle(GetCurrentDrawData() ? GetCurrentDrawData()->szTitle : "");
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::UpdateEditView()
{
	CView * pView = GetCEditView();
	if( pView )
	{
		::SetWindowText(pView->GetSafeHwnd(), (LPCSTR)gResultOutput);
		pView->UpdateWindow();
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::Clear()
{
	m_bTautomer = m_bMetal = FALSE;
	m_bWriteToDisk = FALSE;
	m_bNPZZ = FALSE;
	m_bFoldCRU = FALSE;
	m_bPolymers = FALSE;
	m_bNoPolymerEdits = FALSE;
	m_bNoFrameShift = FALSE;
	m_bZzAsStar = TRUE;
	::free_drawing_vec();
	gResultOutput.Empty();
	if( !m_bKeepComponent )
		ResetCtrls();
	UpdateWINChIView();
	UpdateEditView();
}


/////////////////////////////////////////////////////////////////////////////
void  freeINChI(INChIParams*& pINChIParams)
{
	if( pINChIParams )
	{
		CleanUp_(pINChIParams);
		free( pINChIParams );
		pINChIParams = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void  CWINChIDoc::FreeINChI()
{
	freeINChI(m_pINChIParams);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::FreeBatchINChI()
{
	freeINChI(m_pINChIBatchParams);
}

/////////////////////////////////////////////////////////////////////////////
const DrawData * CWINChIDoc::GetDrawData(int nComp, int nRadio, BOOL bTaut, BOOL bMet)
{
	static int res_taut[] = {COMPONENT_TI,COMPONENT_BI,COMPONENT_TN,COMPONENT_BN};
	static int res_non_taut[] = {COMPONENT_BI,COMPONENT_TI,COMPONENT_BN,COMPONENT_TN};
	const struct DrawDataAr& DrawingVec = get_current_draw_vec(bMet ? 1: 0);
	if( nComp < 0 || nComp > DrawingVec.nComp || nRadio < IDC_RADIO_ORIGINAL || nRadio > IDC_RADIO_RES )
		return NULL;
	BOOL b_IgnoreIso = m_Dlg.m_Dlg.m_IgnoreIso;
	int nType;
	switch(nRadio)
	{
	case IDC_RADIO_ORIGINAL	:
		nType = COMPONENT_ORIGINAL;
		break;
	case IDC_RADIO_PREPROCESSED:
		nType = COMPONENT_ORIGINAL_PREPROCESSED;
		break;
	case IDC_RADIO_RES:
		if(b_IgnoreIso) 
		{
			nType = bTaut ? COMPONENT_TN : COMPONENT_BN;
			if( !DrawingVec.v[nComp][nType])
				nType = bTaut ? COMPONENT_BN : COMPONENT_TN;
		}
		else
		{
			int * c_type = bTaut ? res_taut : res_non_taut;
			nType = c_type[3];
			for( int i = 0; i < 3; i++ )
			{
				if(DrawingVec.v[nComp][c_type[i]])
				{
					nType = c_type[i];
					break;
				}
			}
		}
		break;
	default:
		return NULL;
	}
	return DrawingVec.v[nComp][nType];

}

/////////////////////////////////////////////////////////////////////////////
const DrawData * CWINChIDoc::GetCurrentDrawData(AT_NUMB* nNewEquLabel)
{
	int nComp,  nRadio, nSet;
	BOOL bTaut, bMet, bOriginal,bRet, bNoEdits;

	bRet = ((CMainFrame *)AfxGetMainWnd())->GetCtrlState( nComp, nRadio, nSet,bTaut, bMet, bOriginal, bNoEdits);
	if(nNewEquLabel)
		*nNewEquLabel = nSet;
	return bRet ? GetDrawData(nComp, nRadio, bTaut, bMet) : NULL;
}



/////////////////////////////////////////////////////////////////////////////
// CWINChIDoc commands


/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnFileOpen() 
{
	if( m_Dlg.DoModal() != IDOK )
		return;

	ProcessInput(FALSE);

}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::RunExternalFile(const CString& fname, BOOL bMerge)
{
	SECFileSystem fs;
	if( fs.FileExists(fname) )
	{
		m_Dlg.m_InputFile = fname;
		m_Dlg.m_bMerge = bMerge;
		ProcessInput(FALSE);
	}
	else
	{
		::AfxMessageBox(fname + " Not found");
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::ProcessInput(BOOL bBatch, int how)
{
	CString str;
	CStringArray ar, opt;

	int nComp,  nRadio, nSet;
	BOOL bTaut, bMet, bOriginal, bNoEdits;

	
	INCHI_IOS_STRING *strbuf; /* = &temp_string_container;*/
	
	INCHI_CLOCK *pic;
	CANON_GLOBALS *pCG;

	pCG = & ((CWINChIApp*)AfxGetApp())->CG;
	pic = & ((CWINChIApp*)AfxGetApp())->ic;

	memset( pCG, 0, sizeof(*pCG));
	memset( pic, 0, sizeof(*pic));

	strbuf = & ((CWINChIApp*)AfxGetApp())->temp_string_container;


	/*
	CANON_GLOBALS *pCG;
	INCHI_CLOCK ic;
	INCHI_CLOCK *pic;
	pCG = & ((CWINChIApp*)AfxGetApp())->CG;
	pic = pic;
	memset( pCG , 0, sizeof(CANON_GLOBALS *) );
	memset( pic, 0, sizeof(ic));
	*/

	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, bMet, bOriginal, bNoEdits);


	ar.Add(m_Dlg.m_InputFile);
	if( bBatch ) // add other files
	{
		char path[_MAX_PATH], fname[_MAX_FNAME];
		strcpy(path, (LPCSTR)m_Dlg.m_InputFile);
		_splitpath(path,NULL,NULL,fname,NULL);

#if 0
			/* TODO: add dialog-switchable control variable */
			/* TODO: add the same behavior to non-batch proicessing */
			AddTimeStampToFilePath( fname );
#endif

		m_OutputFile = ((CWINChIApp*)AfxGetApp())->m_StartUpDir + fname + ".txt";
		if( stricmp((LPCSTR) m_Dlg.m_InputFile, (LPCSTR)m_OutputFile ) == 0 ) 
			m_OutputFile += ".txt";

		m_LogFile = ((CWINChIApp*)AfxGetApp())->m_StartUpDir + fname + ".log";
		if( stricmp((LPCSTR) m_Dlg.m_InputFile, (LPCSTR)m_LogFile ) == 0 )
			m_LogFile += ".log";

		m_ProblemFile = ((CWINChIApp*)AfxGetApp())->m_StartUpDir + fname + ".prb";
		if( stricmp((LPCSTR) m_Dlg.m_InputFile, (LPCSTR)m_ProblemFile ) == 0 )
			m_ProblemFile += ".prb";

		
		ar.Add(m_OutputFile);
		ar.Add(m_LogFile);
		ar.Add(m_ProblemFile);

	}
	else
	{
		//ar.Add("NUL");
		//ar.Add("NUL");
		//ar.Add("NUL");
		ar.Add("/D");
	}

	
	ar.Add("/I");


#ifndef INCHI_VER_103
	if( !bMet )
		ar.Add("/RECONMETAL:0");
	ar.Add("/T");
	if(!bTaut)
		ar.Add("/B");

	ar.Add("/SPXYZ");
	ar.Add("/SASXYZ");
	ar.Add("/FB");
	ar.Add("/FB2"); // new
	ar.Add("/FNUD");
	ar.Add("/NOUUSB");
	ar.Add("/NOUUSC");
	ar.Add("/AUXINFO:1");
#else 
	if( bMet )
		ar.Add("/RecMet");
	if( !bTaut )
		ar.Add("/FixedH");
	ar.Add("/XHAsh1");
	ar.Add("/XHAsh2");
	//ar.Add("/SaveOpt");
#endif


	ar.Add("/PLAIN");
	ar.Add("/KEY");

	int Write2Disk = 0;
	m_Dlg.GetOptions(opt, &Write2Disk );
	
	ar.Append(opt);
	if( bBatch )
	{
		m_pINChIBatchParams = (INChIParams *)calloc(sizeof(INChIParams), 1);

		m_pINChIBatchParams->ic = pic;
		m_pINChIBatchParams->pCG = pCG;
		m_pINChIBatchParams->strbuf = strbuf;
	}
	else
	{
		STRUCT_FPTRS * ps_f = NULL;
		m_bKeepComponent = how == 2;
		Clear();
		if( how != 0 && m_pINChIParams)
		{
			ps_f = (STRUCT_FPTRS *) malloc(sizeof(STRUCT_FPTRS));
			*ps_f = m_pINChIParams->Fptrs;
			memset(&m_pINChIParams->Fptrs, 0, sizeof(m_pINChIParams->Fptrs));
		}

		FreeINChI();
		m_pINChIParams = (INChIParams *)calloc(sizeof(INChIParams), 1);
		if( ps_f )
		{
			m_pINChIParams->Fptrs = *ps_f;
			free(ps_f);
		}

		m_pINChIParams->ic = pic;
		m_pINChIParams->pCG = pCG;
		m_pINChIParams->strbuf = strbuf;
	}

	char * argv[20];
	int i, argc = ar.GetSize() +1;
	argv[0] = "";
	for( i = 0; i < ar.GetSize(); i++ )
	{
		argv[i+1] = ar[i].GetBuffer(ar[i].GetLength());
	}

	int disk_out = bBatch ? 1 : ( Write2Disk ? 1 : 0 );

	int err = !::Initialize_( argc, argv, 
							  bBatch ? m_pINChIBatchParams : m_pINChIParams, 
							  disk_out );

/*
	FILE *debout;
	debout = _tfopen( "N:/qq.txt", _T("wt") );
	//fwrite( "qq!\n", 1, 1, debout );
	for(int k=0; k<argc-1; k++)
		fprintf(debout,"%-s ",argv[k]);
	fprintf(debout,"%-s\"\n", argv[argc-1]);
	fclose(debout);
*/
	for( i = 0; i < ar.GetSize(); i++ )
	{
		ar[i].ReleaseBuffer();
	}

	if( err )
	{
		::AfxMessageBox("Error processing data");
		if( bBatch )
		{
			FreeBatchINChI();
		}
		else
		{
			ResetCtrls();
			UpdateEditView();
			FreeINChI();
		}
		return;
	}
	if( gbBatch = bBatch )
	{
		gbCanceled = FALSE;
		gThreadData.pINChIParams = m_pINChIBatchParams;
		gThreadData.pf = thread_callback; 

		SetStatusText("Working..." );
		::AfxBeginThread( ThreadBatchFunction,&gThreadData);
		
	}
	else
	{
		GetStructure();
	}
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !gbThreadON );
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::GetStructure()
{
	Clear();
	CleanOneStructData_(m_pINChIParams);
	
	int nRet = GetOneStructure( m_pINChIParams->ic,
								&m_pINChIParams->struct_data, 
								&m_pINChIParams->inp_parms, 
								m_pINChIParams->szTitle, 
								&m_pINChIParams->inp_file, 
								&m_pINChIParams->log_file, 
								&m_pINChIParams->output_file, 
								&m_pINChIParams->prb_file, 
								&m_pINChIParams->OrigAtData, 
								&m_pINChIParams->num_inp, 
								&m_pINChIParams->Fptrs );


	if ( nRet == _IS_EOF )
	{
		ResetCtrls();
		FreeINChI();
		OnFileOpen();
	}
	else if ( nRet == _IS_ERROR || nRet == _IS_SKIP )
	{
		ResetCtrls();
		UpdateEditView();
	}
	else if ( nRet == _IS_FATAL )
	{
		ResetCtrls();
		UpdateEditView();
		FreeINChI();
	}
	else
	{
		// starting thread
		gbCanceled = FALSE;
		gThreadData.pINChIParams = m_pINChIParams;
		gThreadData.pf =thread_callback; 
		SetStatusText("Working...");
		::AfxBeginThread( ThreadFunction,&gThreadData);
	}
	
	if ( m_pINChIParams->output_file.f )	
	{
		fflush( m_pINChIParams->output_file.f );
	}
	if ( m_pINChIParams->log_file.f )		
	{
		fflush( m_pINChIParams->log_file.f );
	}
	if ( m_pINChIParams->prb_file.f )		
	{
		fflush( m_pINChIParams->prb_file.f );
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::JustReadStructure()
{
	Clear();
	CleanOneStructData_(m_pINChIParams);
	
	int nRet = GetOneStructure( m_pINChIParams->ic,
								&m_pINChIParams->struct_data, 
								&m_pINChIParams->inp_parms, 
								m_pINChIParams->szTitle, 
								&m_pINChIParams->inp_file, 
								&m_pINChIParams->log_file, 
								&m_pINChIParams->output_file, 
								&m_pINChIParams->prb_file, 
								&m_pINChIParams->OrigAtData, 
								&m_pINChIParams->num_inp, 
								&m_pINChIParams->Fptrs );


	if ( nRet == _IS_EOF )
	{
		ResetCtrls();
		FreeINChI();
		OnFileOpen();
	}
	else if ( nRet == _IS_ERROR || nRet == _IS_SKIP )
	{
		ResetCtrls();
		UpdateEditView();
	}
	else if ( nRet == _IS_FATAL )
	{
		ResetCtrls();
		UpdateEditView();
		FreeINChI();
	}
	else
	{
		; // do nothing, just consume structure
	}
	

	return;
}

/////////////////////////////////////////////////////////////////////////////
int get_pos(STRUCT_FPTRS * s_f, int offset)
{
	int pos = s_f->cur_fptr +offset;
	if( pos < 0 || pos >= s_f->max_fptr )
	{
		return -1;
	}
	if( !(pos == 0 && s_f->max_fptr == 0 ) && s_f->fptr[pos] == EOF )
	{		
		return -1;
	}
	return pos;
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::GetOffsetStructure(int offset)
{
	if( !m_pINChIParams )
	{
		return;
	}
	int pos = get_pos(&m_pINChIParams->Fptrs,offset);
	if( pos != -1 )
	{
		m_pINChIParams->Fptrs.cur_fptr = pos;
		GetStructure();
	}
}


/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::MoveToRecord(int nrecord) 
{
	int i, pos, nrecords2move = 0;
		
	if( !m_pINChIParams )
	{
		return;
	}
	nrecords2move = nrecord - (m_pINChIParams->Fptrs.cur_fptr+1);
	if (nrecords2move<0)
	{
		GetOffsetStructure(nrecords2move);
	}
	else if (nrecords2move>0)
	{
		for (i=0; i<nrecords2move; i++)
		{
			pos = get_pos(&m_pINChIParams->Fptrs,1);
			if( pos != -1 )
			{
				m_pINChIParams->Fptrs.cur_fptr = pos;
				JustReadStructure();
			}
			else
			{
				GetStructure();
				break;
			}
		}
		if (pos!=-1)
		{
			GetStructure();
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnViewNextStru() 
{
	GetOffsetStructure(1);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateViewNextStru(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pINChIParams != NULL && !gbThreadON && get_pos(&m_pINChIParams->Fptrs,1) != -1);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnViewGotoStru() 
{
	long int dest=-1;
	//	GetOffsetStructure(1);
		//long int nback = -10; //(cur_fptr+1) - 10;
	//GetOffsetStructure(nback);
	//MoveToRecord(25) ;
    if( m_GoToDlg.DoModal() == IDOK )
    {
		dest = m_GoToDlg.m_GoToNumber;
		
		BeginWaitCursor( );

		MoveToRecord(dest);

		EndWaitCursor( );
    }
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateViewGotoStru(CCmdUI* pCmdUI) 
{
	;//pCmdUI->Enable( m_pINChIParams != NULL && !gbThreadON && get_pos(&m_pINChIParams->Fptrs,1) != -1);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnViewPrevStru() 
{
	GetOffsetStructure(-1);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateViewPrevStru(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pINChIParams != NULL && !gbThreadON && get_pos(&m_pINChIParams->Fptrs,-1) != -1);
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnViewCancel() 
{
	gbCanceled	= TRUE;

}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateViewCancel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( gbThreadON );
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnFileProcessAll() 
{
	ProcessInput(TRUE);
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateFileProcessAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pINChIParams != NULL && !gbThreadON );
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnOptions() 
{
	if( m_Dlg.m_Dlg.DoModal() == IDOK )
	{
		//		change controls
		CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
				(WPARAM)TRUE, 0, TRUE, TRUE);


		if( !m_Dlg.m_InputFile.IsEmpty() )
			ProcessInput(FALSE,1);

	}
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateOptions(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !gbThreadON );
}


/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnThreadFinished() 
{
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->SetComboFocus();
	::SetStatusText("Ready");
	if( gbBatch )
	{
		CString Str1;
		gbBatch = FALSE;

		if( !gbCanceled )
		{
			CString Str2;

			if( m_pINChIBatchParams->num_inp == 1 )
			{
				Str2 = "\n\n1 structure total.\n\n";
			}
			else
			{
				Str2.Format("\n\n%d structures total\n\n", m_pINChIBatchParams->num_inp);
			}
			Str1 = m_Dlg.m_InputFile + Str2;

			Str2.Format("Following files have been created:\n\nResult File:\t%s\nLog File:      \t%s\nProblem File:\t%s",
				(LPCSTR)m_OutputFile, (LPCSTR)m_LogFile, (LPCSTR)m_ProblemFile);
			Str1 += Str2;
		}
		FreeBatchINChI();
		if( !Str1.IsEmpty() )
		{
			::AfxMessageBox(Str1);
		}

		ProcessInput( FALSE ); //^^^ v. 1.051 to re-init log/out/prb file/screen output

	}
	else
	{
		gDrawingVec[0].nComp = m_pINChIParams->PrepAtData[0].num_components;
		gDrawingVec[0].nSortedOrder = m_pINChIParams->PrepAtData[0].nSortedOrder;
		gDrawingVec[1].nComp = m_pINChIParams->PrepAtData[1].num_components;
		gDrawingVec[1].nSortedOrder = m_pINChIParams->PrepAtData[1].nSortedOrder;
		m_bMetal = (m_pINChIParams->struct_data.bTautFlagsDone[INCHI_BAS] & TG_FLAG_DISCONNECT_COORD_DONE) != 0;
		m_bTautomer = (gDrawingVec[0].nComp > 0 && m_pINChIParams->struct_data.num_taut[0]) || (gDrawingVec[1].nComp > 0 && m_pINChIParams->struct_data.num_taut[1]);

		CEditView *pView = GetCEditView();
		if( pView )
		{
			::SetWindowText(pView->GetSafeHwnd(), (LPCSTR)gResultOutput);
			pView->UpdateWindow();
		}
		if( !m_bKeepComponent )
		{
			InitCtrls();
		}
		else
		{
			// Now preprocessed might dissapear, so we need to check if selected component is present
			int nComp,  nRadio, nSet;
			BOOL bMet, bOriginal, bNoEdits;
			pFrame->GetCtrlState( nComp, nRadio, nSet,m_Dlg.m_Dlg.m_bTaut, bMet, bOriginal, bNoEdits);
			if( !IsRadioEnable( nRadio ) )
			{
				pFrame->CheckRadio( IDC_RADIO_ORIGINAL );
			}


			OnRadio();
			m_bKeepComponent = FALSE;
		}
	}

	gbCanceled = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnSelchangeComponents() 
{
	int nComp,  nRadio, nSet;
	BOOL bTaut, bMet, bOriginal, bNoEdits;

	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, bMet, bOriginal, bNoEdits);
	if( !bOriginal && !m_bCompSelected && IsRadioEnable(IDC_RADIO_RES) )
	{
		pFrame->CheckRadio(IDC_RADIO_RES);
	}
	else if(!IsRadioEnable(nRadio) )
	{
		pFrame->CheckRadio(IDC_RADIO_ORIGINAL);
	}
	m_bCompSelected = !bOriginal;
	OnRadio();

}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnRadio() 
{
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	const DrawData * pDrawData = GetCurrentDrawData();
	int sets = 0;
	if( pDrawData && pDrawData->pWindowData->nEquLabels && pDrawData->pWindowData->nNumEquSets)
	{
		sets = pDrawData->pWindowData->nNumEquSets;
	}
	pFrame->SetRangeAndPos(sets,0);
	OnEdtChange();
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnEdtChange()
{
	UpdateWINChIView();
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateComponents(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_pINChIParams != NULL && !gbThreadON );
}

/////////////////////////////////////////////////////////////////////////////
BOOL CWINChIDoc::IsRadioEnable(int nRadioID)
{
	int nComp,  nRadio, nSet;
	BOOL bTaut, bMet, bOriginal, bNoEdits;

	if( !m_pINChIParams || gbThreadON )
	{
		return FALSE;
	}

	BOOL bRet = ((CMainFrame *)AfxGetMainWnd())->GetCtrlState( nComp, nRadio, nSet, bTaut, bMet, bOriginal, bNoEdits);
	return bRet && NULL != GetDrawData(nComp, nRadioID, bTaut, bMet);
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateRadioOriginal(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	IsRadioEnable(IDC_RADIO_ORIGINAL));
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateRadioPreprocessed(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	IsRadioEnable(IDC_RADIO_PREPROCESSED));
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateRadioRes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	IsRadioEnable(IDC_RADIO_RES));
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnEditPaste() 
{
	static const char * FileName = "winchi_clipboard.mol";
	if( ::IsMDLClipboardAvailable( )  && 0 == ::GetMDLClipboardData( AfxGetMainWnd()->GetSafeHwnd(), FileName ) )
	{
		RunExternalFile(FileName, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::IsMDLClipboardAvailable());	
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::InitCtrls()
{
	CStringArray str_ar;
	CUIntArray int_ar;
	CString str;
	int nComp,  nRadio, nSet;
	BOOL bTaut, bMet, bOriginal, bNoEdits;

	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	if( m_pINChIParams )
	{
		pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, bMet, bOriginal, bNoEdits);
		const struct DrawDataAr& DrawingVec = get_current_draw_vec(bMet ? 1: 0);
		if( DrawingVec.nComp == 1 )
		{
			str_ar.Add("Single Structure");
			int_ar.Add(1);
		}
		else
		{
			str_ar.Add("Input Structure");
			int_ar.Add(0);
			for( int i = 1; i <= DrawingVec.nComp; i++ )
			{
				str.Format("Component #%d",i);
				str_ar.Add(str);
				int_ar.Add(DrawingVec.nSortedOrder ? DrawingVec.nSortedOrder[i] : i);
			}
		}
	}
	pFrame->InitCtrls(str_ar, int_ar);
	if(IsRadioEnable(IDC_RADIO_RES))
	{
		pFrame->CheckRadio(IDC_RADIO_RES);
	}
	m_bCompSelected = FALSE;
	OnSelchangeComponents();
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::ResetCtrls()
{
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->ResetCtrls();
	m_bKeepComponent = m_bCompSelected = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnCheckRec() 
{
	// TODO: Add your command handler code here
	int nComp,  nRadio, nSet;
	BOOL bTaut, bOriginal, bNoEdits;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, m_Dlg.m_Dlg.m_bMetal, bOriginal, bNoEdits);
	if( !m_Dlg.m_InputFile.IsEmpty() )
	{
		ProcessInput(FALSE,1);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnCheckTaut() 
{
	// TODO: Add your command handler code here
	int nComp,  nRadio, nSet;
	BOOL bMet, bOriginal, bNoEdits;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,m_Dlg.m_Dlg.m_bTaut, bMet, bOriginal, bNoEdits);
	/*
	if( !IsRadioEnable( nRadio ) )
	{
		pFrame->CheckRadio( IDC_RADIO_ORIGINAL );
	}
	*/
	if( !m_Dlg.m_InputFile.IsEmpty() )
	{
		ProcessInput(FALSE,2);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnCheckNoEdits() 
{
	int nComp,  nRadio, nSet;
	BOOL bTaut, bOriginal, bMetal;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, bMetal, bOriginal, m_Dlg.m_Dlg.m_bNoEdits);
	if( !m_Dlg.m_InputFile.IsEmpty() )
	{
		ProcessInput(FALSE,1);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateCheckRec(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Dlg.m_Dlg.m_bMetal);

#if 0

#ifdef STD_WINCHI
	pCmdUI->Enable(FALSE);
#else
	pCmdUI->Enable( !gbThreadON && (!m_pINChIParams || m_bMetal) );
#endif

#endif

}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateCheckTaut(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Dlg.m_Dlg.m_bTaut);	
	return;
#if 0

#ifdef STD_WINCHI
		pCmdUI->Enable(FALSE);
		return;
#endif

	if( gbThreadON )
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		int nComp,  nRadio, nSet;
		BOOL bMet, bOriginal, bRet, bNoEdits;
		CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
		bRet = pFrame->GetCtrlState( nComp, nRadio, nSet,m_Dlg.m_Dlg.m_bTaut, bMet, bOriginal, bNoEdits);
		if(!m_pINChIParams || !bRet)
			pCmdUI->Enable(TRUE);
		else
		{
			if( bOriginal )
			{
				pCmdUI->Enable(m_bTautomer);
			}
			else
			{
				const struct DrawDataAr& DrawingVec = get_current_draw_vec(bMet ? 1: 0);
				BOOL b_IgnoreIso = m_Dlg.m_Dlg.m_IgnoreIso;
				ASSERT( nComp >= 0 && nComp <= DrawingVec.nComp && nRadio >= IDC_RADIO_ORIGINAL && nRadio <= IDC_RADIO_RES );
				if(b_IgnoreIso) 
				{
					pCmdUI->Enable(DrawingVec.v[nComp][COMPONENT_TN] != NULL);
				}
				else
				{
					pCmdUI->Enable(DrawingVec.v[nComp][COMPONENT_TN] != NULL || DrawingVec.v[nComp][COMPONENT_TI] != NULL);
				}
			}
		}
	}
#endif
	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnUpdateCheckNoEdits(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Dlg.m_Dlg.m_bNoEdits);	
}

/////////////////////////////////////////////////////////////////////////////
void CWINChIDoc::OnCheckWriteLogs() 
{
	int nComp,  nRadio, nSet;
	BOOL bTaut, bOriginal, bNoEdits;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->GetCtrlState( nComp, nRadio, nSet,bTaut, m_Dlg.m_Dlg.m_bMetal, bOriginal, bNoEdits);
	m_bWriteToDisk = m_Dlg.m_Dlg.m_bWriteToDisk;
	if( !m_Dlg.m_InputFile.IsEmpty() )
	{
		ProcessInput(FALSE,1);
	}
	
}
