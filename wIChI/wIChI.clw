; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgGoTo
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wichi.h"
LastPage=0

ClassCount=10
Class1=Bar
Class2=CDlgInchiOption
Class3=DlgOptions
Class4=CMainFrame
Class5=CTextView
Class6=CWINChIApp
Class7=CAboutDlg
Class8=CWINChIDoc
Class9=CWINChIView

ResourceCount=17
Resource1=IDD_INCHI_OPTIONS_DIALOG
Resource2=IDD_ABOUTBOX (English (U.S.) - STD_WINCHI)
Resource3=IDD_DIALOG1
Resource4=IDR_MENU1
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDD_ABOUTBOX (STD_WINCHI)
Resource7=IDR_WINCHI_MENU (English (U.S.))
Resource8=IDR_WINCHI_MENU
Resource9=IDD_INCHI_OPTIONS_DIALOG (English (U.S.))
Resource10=IDD_DIALOG1 (English (U.S.))
Resource11=IDR_MAINFRAME
Resource12=IDR_MENU1 (English (U.S.))
Resource13=IDD_DIALOGBAR (English (U.S.))
Resource14=IDD_ABOUTBOX (English (U.S.))
Resource15=IDD_ABOUTBOX
Resource16=IDD_DIALOGBAR
Class10=CDlgGoTo
Resource17=IDD_DIALOG_GOTO

[CLS:Bar]
Type=0
HeaderFile=src\bar.h
ImplementationFile=src\bar.cpp
BaseClass=CDialogBar
LastObject=Bar

[CLS:CDlgInchiOption]
Type=0
HeaderFile=src\dlgichioption.h
ImplementationFile=src\dlgichioption.cpp
BaseClass=CDialog
LastObject=IDC_CHECK_TAUT
Filter=D
VirtualFilter=dWC

[CLS:DlgOptions]
Type=0
BaseClass=CDialog
HeaderFile=DlgOptions.h
ImplementationFile=DlgOptions.cpp
LastObject=DlgOptions

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CTextView]
Type=0
BaseClass=CEditView
HeaderFile=TextView.h
ImplementationFile=TextView.cpp

[CLS:CWINChIApp]
Type=0
BaseClass=CWinApp
HeaderFile=wIChI.h
ImplementationFile=wIChI.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=wIChI.cpp
ImplementationFile=wIChI.cpp

[CLS:CWINChIDoc]
Type=0
HeaderFile=src\wichidoc.h
ImplementationFile=src\wichidoc.cpp
BaseClass=CDocument
Filter=N
LastObject=ID_EDIT_PASTE_STRUCT
VirtualFilter=DC

[CLS:CWINChIView]
Type=0
BaseClass=CView
HeaderFile=wIChIView.h
ImplementationFile=wIChIView.cpp

[DLG:IDD_DIALOGBAR]
Type=1
Class=Bar
ControlCount=22
Control1=ID_FILE_OPEN,button,1342242816
Control2=ID_OPTIONS,button,1342242816
Control3=ID_VIEW_PREV_STRU,button,1342242816
Control4=ID_VIEW_NEXT_STRU,button,1342242816
Control5=ID_FILE_ALL,button,1342242816
Control6=ID_VIEW_CANCEL,button,1342242816
Control7=IDC_STATIC_RESULTS,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=ID_COMPONENTS,combobox,1344339971
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO_ORIGINAL,button,1342177289
Control12=IDC_RADIO_PREPROCESSED,button,1342177289
Control13=IDC_RADIO_RES,button,1342177289
Control14=IDC_STATIC,button,1342177287
Control15=IDC_CHECK_TAUT,button,1342373891
Control16=IDC_CHECK_REC,button,1342373891
Control17=IDC_STATIC_NSETS,button,1342177287
Control18=IDC_STATIC_EQ,static,1342308352
Control19=IDC_SPIN1,msctls_updown32,1342177318
Control20=IDC_EDIT_SPIN,edit,1350641792
Control21=IDC_STATIC,static,1342308352
Control22=IDC_CHECK_NOEDITS,button,1342242819

[DLG:IDD_INCHI_OPTIONS_DIALOG]
Type=1
Class=CDlgInchiOption
ControlCount=28
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK_TAUT,button,1342373891
Control3=IDC_CHECK_STEREO,button,1342242819
Control4=IDC_RADIO_ABS,button,1342308361
Control5=IDC_RADIO_REL,button,1342177289
Control6=IDC_RADIO_REC,button,1342177289
Control7=IDC_RADIO_UCF,button,1342177289
Control8=IDC_CHECK_NARROW,button,1342242819
Control9=IDC_CHECK_REC,button,1342373891
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CHECK_DISABLE,button,1342242819
Control12=IDC_STATIC,button,1342177287
Control13=IDC_RADIO_PLAIN,button,1342308361
Control14=IDC_RADIO_XML,button,1476395017
Control15=IDC_RADIO_NONE,button,1342177289
Control16=IDC_CHECK_IGNORE_ISO,button,1342242819
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816
Control19=IDC_CHECK_TAUTO_15,button,1342242819
Control20=IDC_CHECK_SUU,button,1342242819
Control21=IDC_CHECK_SLUUD,button,1342242819
Control22=IDC_CHECK_WRITE_LOGS,button,1342242819
Control23=IDC_CHECK_TREAT_POLYMERS,button,1342242819
Control24=IDC_CHECK_NOEDITS,button,1342242819
Control25=IDC_CHECK_NPZZ,button,1342242819
Control26=IDC_CHECK_ZZ_AS_STAR,button,1476460547
Control27=IDC_CHECK_FOLDCRU,button,1342242819
Control28=IDC_NO_FRAMESHIFT,button,1342242819

[DLG:IDD_DIALOG1]
Type=1
Class=DlgOptions
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT_SDFID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_INPUT_FILE,edit,1350633600
Control7=IDC_BUTTON_ADV,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_NEXT_STRU
Command3=ID_VIEW_PREV_STRU
Command4=ID_VIEW_GOTO_STRU
Command5=ID_FILE_ALL
Command6=ID_OPTIONS
Command7=ID_VIEW_CANCEL
Command8=ID_FILE_PRINT_SETUP
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE_STRUCT
Command14=ID_APP_ABOUT
CommandCount=14

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_THREAD_FINISHED
Command2=ID_COMPONENTS
Command3=IDC_RADIO_ORIGINAL
Command4=IDC_RADIO_PREPROCESSED
Command5=IDC_CHECK_TAUT
Command6=IDC_CHECK_REC
Command7=IDC_RADIO_RES
CommandCount=7

[MNU:IDR_WINCHI_MENU]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_NEXT_STRU
Command3=ID_VIEW_PREV_STRU
Command4=ID_FILE_ALL
Command5=ID_OPTIONS
Command6=ID_VIEW_CANCEL
Command7=ID_EDIT_PASTE_STRUCT
Command8=ID_FILE_PRINT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_VIEW_GOTO_STRU
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE_STRUCT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE_STRUCT
Command13=ID_VIEW_PREV_STRU
Command14=ID_VIEW_NEXT_STRU
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[DLG:IDD_ABOUTBOX (STD_WINCHI)]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_ABOUTBOX (English (U.S.) - STD_WINCHI)]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_DIALOG1 (English (U.S.))]
Type=1
Class=DlgOptions
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT_SDFID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_INPUT_FILE,edit,1350633600
Control7=IDC_BUTTON_ADV,button,1342242816

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=Bar
ControlCount=21
Control1=ID_FILE_OPEN,button,1342242816
Control2=ID_OPTIONS,button,1342242816
Control3=ID_VIEW_PREV_STRU,button,1342242816
Control4=ID_VIEW_NEXT_STRU,button,1342242816
Control5=ID_FILE_ALL,button,1342242816
Control6=ID_VIEW_CANCEL,button,1342242816
Control7=IDC_STATIC_RESULTS,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=ID_COMPONENTS,combobox,1344339971
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO_ORIGINAL,button,1342177289
Control12=IDC_RADIO_PREPROCESSED,button,1342177289
Control13=IDC_RADIO_RES,button,1342177289
Control14=IDC_STATIC,button,1342177287
Control15=IDC_CHECK_TAUT,button,1342373891
Control16=IDC_CHECK_REC,button,1342373891
Control17=IDC_STATIC_NSETS,button,1342177287
Control18=IDC_STATIC_EQ,static,1342308352
Control19=IDC_SPIN1,msctls_updown32,1342177318
Control20=IDC_EDIT_SPIN,edit,1350641792
Control21=IDC_STATIC,static,1342308352

[DLG:IDD_INCHI_OPTIONS_DIALOG (English (U.S.))]
Type=1
Class=CDlgInchiOption
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK_TAUT,button,1342373891
Control3=IDC_CHECK_STEREO,button,1342242819
Control4=IDC_RADIO_ABS,button,1342308361
Control5=IDC_RADIO_REL,button,1342177289
Control6=IDC_RADIO_REC,button,1342177289
Control7=IDC_RADIO_UCF,button,1342177289
Control8=IDC_CHECK_NARROW,button,1342242819
Control9=IDC_CHECK_REC,button,1342373891
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CHECK_DISABLE,button,1342242819
Control12=IDC_STATIC,button,1342177287
Control13=IDC_RADIO_PLAIN,button,1342308361
Control14=IDC_RADIO_XML,button,1342177289
Control15=IDC_RADIO_NONE,button,1342177289
Control16=IDC_CHECK_IGNORE_ISO,button,1342242819
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816
Control19=IDC_CHECK_TAUTO_15,button,1342242819
Control20=IDC_CHECK_SUU,button,1342242819
Control21=IDC_CHECK_SLUUD,button,1342242819

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_NEXT_STRU
Command3=ID_VIEW_PREV_STRU
Command4=ID_FILE_ALL
Command5=ID_OPTIONS
Command6=ID_VIEW_CANCEL
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE_STRUCT
Command13=ID_APP_ABOUT
CommandCount=13

[MNU:IDR_MENU1 (English (U.S.))]
Type=1
Class=?
Command1=ID_THREAD_FINISHED
Command2=ID_COMPONENTS
Command3=IDC_RADIO_ORIGINAL
Command4=IDC_RADIO_PREPROCESSED
Command5=IDC_CHECK_TAUT
Command6=IDC_CHECK_REC
Command7=IDC_RADIO_RES
CommandCount=7

[MNU:IDR_WINCHI_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_VIEW_NEXT_STRU
Command3=ID_VIEW_PREV_STRU
Command4=ID_FILE_ALL
Command5=ID_OPTIONS
Command6=ID_VIEW_CANCEL
Command7=ID_EDIT_PASTE_STRUCT
Command8=ID_FILE_PRINT
CommandCount=8

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE_STRUCT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE_STRUCT
Command12=ID_EDIT_CUT
Command13=ID_EDIT_UNDO
CommandCount=13

[DLG:IDD_DIALOG_GOTO]
Type=1
Class=CDlgGoTo
ControlCount=3
Control1=IDC_EDIT_GOTO_NUMBER,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CDlgGoTo]
Type=0
HeaderFile=DlgGoTo.h
ImplementationFile=DlgGoTo.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgGoTo

