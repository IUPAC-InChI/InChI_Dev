# Microsoft Developer Studio Project File - Name="vc6_INCHI_DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vc6_INCHI_DLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vc6_INCHI_DLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vc6_INCHI_DLL.mak" CFG="vc6_INCHI_DLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vc6_INCHI_DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vc6_INCHI_DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vc6_INCHI_DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCHI_LINK_AS_DLL" /YX /FD /c
# ADD CPP /MT /W3 /GX /Ox /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCHI_LINK_AS_DLL" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /machine:I386 /def:".\vc6_libstdinchi.def" /out:"Release/libstdinchi.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "vc6_INCHI_DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCHI_LINK_AS_DLL" /YX /FD /GZ /c
# ADD CPP /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "INCHI_LINK_AS_DLL" /Fr /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/InCHI_DLL.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /debug /machine:I386 /def:".\vc6_libstdinchi.def" /out:"Debug/libstdinchi.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "vc6_INCHI_DLL - Win32 Release"
# Name "vc6_INCHI_DLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\INCHI_DLL\ichi_bns.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichi_io.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichican2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichicano.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichicans.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiisot.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichilnct.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichimak2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichimake.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichimap1.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichimap2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichimap4.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichinorm.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiparm.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiprt1.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiprt2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiprt3.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiqueu.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiread.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichiring.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr1.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr3.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr4.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr5.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr6.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvr7.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichisort.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichister.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichitaut.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ikey_base26.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ikey_dll.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchi_dll.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchi_dll_a.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchi_dll_a2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchi_dll_main.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\runichi.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\sha2.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\strutil.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\util.c
# End Source File
# Begin Source File

SOURCE=.\vc6_libstdinchi.def
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\INChI_DLL\aux2atom.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\extr_ct.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichi.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichi_bns.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichi_io.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichicano.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichicant.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichicomn.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichicomp.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichidrp.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichierr.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichimain.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichimake.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichinorm.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichiparm.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichiring.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichirvrs.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichisize.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichister.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\ichitaut.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ichitime.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\ikey_base26.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\inchi_api.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchi_dll_a.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\inchi_dll_main.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\inchicmp.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\incomdef.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\inpdef.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\mode.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_DLL\sha2.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\strutil.h
# End Source File
# Begin Source File

SOURCE=..\INChI_DLL\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\INCHI_DLL.rc
# End Source File
# End Group
# End Target
# End Project
