# Microsoft Developer Studio Project File - Name="IChI_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=IChI_lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IChI_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IChI_lib.mak" CFG="IChI_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IChI_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "IChI_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IChI_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "C:/tmp2/vs6/bin2/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Ot /Oi /Oy /Ob2 /Gy /I "../cmlpp" /I "./cmlpp" /D "NDEBUG" /D TARGET_LIB_FOR_WINCHI=1 /D "WIN32" /D "_MBCS" /D "_LIB" /D "INCHI_LIB" /FD /GF /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"C:/tmp2/vs6/bin2/Release/IChI_lib.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "IChI_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "C:/tmp2/vs6/bin2/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./cmlpp" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "INCHI_LIB" /D TARGET_LIB_FOR_WINCHI=1 /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"C:/tmp2/vs6/bin2/Debug/IChI_lib.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "IChI_lib - Win32 Release"
# Name "IChI_lib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cIChIres.rc
# End Source File
# Begin Source File

SOURCE=.\cINChI11b.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_EXE\inchi-1\src\dispstru.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichi.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichi_bns.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichi_io.c"
# End Source File
# Begin Source File

SOURCE=.\src\IChI_lib.c
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichican2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicano.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicans.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichierr.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiisot.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimak2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimake.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimap1.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimap2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimap4.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichinorm.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiparm.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiprt1.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiprt2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiprt3.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiqueu.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiread.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiring.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr1.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr3.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr4.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr5.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr6.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvr7.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichisort.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichister.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichitaut.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ikey_base26.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ikey_dll.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\inchi_gui.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ixa.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol2atom.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol_fmt1.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol_fmt2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol_fmt3.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol_fmt4.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\readinch.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\runichi.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\runichi2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\runichi3.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\runichi4.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\sha2.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\strutil.c"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\util.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\aux2atom.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_EXE\inchi-1\src\dispstru.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\extr_ct.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichi_bns.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichi_io.h"
# End Source File
# Begin Source File

SOURCE=.\src\ichi_lib.h
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicano.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicant.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicomn.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichicomp.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichidrp.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichierr.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimain.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichimake.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichinorm.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiring.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichirvrs.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichisize.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichister.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichitaut.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichitime.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ikey_base26.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\inchi_api.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\inchi_gui.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\inchicmp.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\incomdef.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\inpdef.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mode.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\mol_fmt.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\readinch.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\sha2.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\strutil.h"
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\util.h"
# End Source File
# End Group
# End Target
# End Project
