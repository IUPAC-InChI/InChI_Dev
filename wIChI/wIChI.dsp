# Microsoft Developer Studio Project File - Name="wIChI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wIChI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wIChI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wIChI.mak" CFG="wIChI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wIChI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wIChI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wIChI - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "C:/tmp2/vs6/bin2/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /Od /I "..\IChI_lib" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "INCHI_VER_103" /D TARGET_LIB_FOR_WINCHI=1 /Fr /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"C:/tmp2/vs6/bin2/Release/wIChI.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 IChI_lib.lib /nologo /subsystem:windows /pdb:"C:/tmp2/vs6/bin2/Release/winchi-1.pdb" /machine:I386 /nodefaultlib:"LIBC" /out:"Release/winchi-1.exe" /libpath:"..\IChI_lib\Release" /libpath:"..\IChI_lib\cmlpp\Release"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "wIChI - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "C:/tmp2/vs6/bin2/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\IChI_lib" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "INCHI_VER_103" /D TARGET_LIB_FOR_WINCHI=1 /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"C:/tmp2/vs6/bin2/Debug/wIChI.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 IChI_lib.lib /nologo /subsystem:windows /pdb:"C:/tmp2/vs6/bin2/Debug/winchi-1.pdb" /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"Debug/winchi-1.exe" /pdbtype:sept /libpath:"..\ICHI_LIB\Debug" /libpath:"..\ICHI_LIB\cmlpp\Debug"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "wIChI - Win32 Release"
# Name "wIChI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\DlgGoTo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DlgIchiOption.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DlgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\src\fthread.cpp
# End Source File
# Begin Source File

SOURCE="..\INCHI-1-SRC\INCHI_BASE\src\ichiparm.c"
# End Source File
# Begin Source File

SOURCE=.\src\isis.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\src\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TextView.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wIChI.cpp
# End Source File
# Begin Source File

SOURCE=.\wIChI.rc
# End Source File
# Begin Source File

SOURCE=.\src\wIChIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wIChIView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\DlgGoTo.h
# End Source File
# Begin Source File

SOURCE=.\src\DlgIchiOption.h
# End Source File
# Begin Source File

SOURCE=.\src\DlgOptions.h
# End Source File
# Begin Source File

SOURCE=.\src\fthread.h
# End Source File
# Begin Source File

SOURCE=.\src\isis.h
# End Source File
# Begin Source File

SOURCE=.\src\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\src\TextView.h
# End Source File
# Begin Source File

SOURCE=.\src\wIChI.h
# End Source File
# Begin Source File

SOURCE=.\src\wIChIDoc.h
# End Source File
# Begin Source File

SOURCE=.\src\wIChIView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wIChI.ico
# End Source File
# Begin Source File

SOURCE=.\res\wIChI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\wIChIDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\wINChI.ico
# End Source File
# Begin Source File

SOURCE=.\res\wINChIDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
