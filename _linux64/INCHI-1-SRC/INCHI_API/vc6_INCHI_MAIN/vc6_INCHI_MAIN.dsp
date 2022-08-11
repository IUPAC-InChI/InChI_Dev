# Microsoft Developer Studio Project File - Name="vc6_INCHI_MAIN" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=vc6_INCHI_MAIN - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vc6_INCHI_MAIN.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vc6_INCHI_MAIN.mak" CFG="vc6_INCHI_MAIN - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vc6_INCHI_MAIN - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "vc6_INCHI_MAIN - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vc6_INCHI_MAIN - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W3 /GX /Ox /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "INCHI_LINK_AS_DLL" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release/INCHI_MAIN.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /map /machine:I386 /out:"../vc6_INCHI_DLL/Release/stdinchi_main.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "vc6_INCHI_MAIN - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "INCHI_LINK_AS_DLL" /Fr /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/INCHI_MAIN.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /map /debug /machine:I386 /out:"../vc6_INCHI_DLL/Debug/stdinchi_main.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "vc6_INCHI_MAIN - Win32 Release"
# Name "vc6_INCHI_MAIN - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\INCHI_MAIN\e_0dstereo.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_ichi_io.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_ichi_parms.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_ichimain.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_ichimain_a.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_inchi_atom.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_mol2atom.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_readinch.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_readmol.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_readstru.c
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\e_util.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\INChI_MAIN\e_0Dstereo.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_comdef.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ctl_data.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ichi_io.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ichi_parms.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ichicomp.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ichierr.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_ichisize.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_inchi_atom.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_inpdef.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_mode.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_readmol.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_readstru.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\e_util.h
# End Source File
# Begin Source File

SOURCE=..\INCHI_MAIN\ichitime.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\inchi_api.h
# End Source File
# Begin Source File

SOURCE=..\INChI_MAIN\lreadmol.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\INCHI_MAIN.rc
# End Source File
# End Group
# End Target
# End Project
