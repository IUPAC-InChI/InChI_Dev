## libinchi.dll, was:
Linker->Input->Module Definition File -> vc9_libinchi.def

/OUT:"../../bin2/Windows/Win32/Debug/libinchi.dll" /MANIFEST /NXCOMPAT /PDB:"../../bin2/Windows/Win32/Debug/libinchi.pdb" /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEF:"vc9_libinchi.def" /STACK:"16000000" /IMPLIB:"../../bin2/Windows/Win32/Debug/libinchi.lib" /DEBUG /DLL /MACHINE:X86 /SAFESEH /INCREMENTAL /PGD:"../../bin2/Windows/Win32/Debug/libinchi.pgd" /SUBSYSTEM:WINDOWS /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"../../bin2/Windows/Win32/Debug/libinchi.tmp\libinchi.dll.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /LIBPATH:"../../tbb/Windows/Win32/Debug/" /TLBID:1 




## inchi_main in i2i mode :
@inchi_main chembl-non-std-16.inc chembl-non-std-16.inchi_main-1051-i2i.out chembl-non-std-16.inchi_main-1051-i2i.log /inchi2inchi /AuxNone /fixedh /recmet"

in directory "I:\Dropbox\work\INCHI\ref\data\105\i2i\chembl23\inchi-1\" makes totally nonsense;
produces .prb file ~250MB with diagnostics""Fatal Error 3 (aborted; Too long counts line; Cannot interpret counts line:...) inp structure #1")


## mol2inchi props
---------------

### vc14

### General

### output dir 
../../../bin2/Windows/$(Platform)/$(Configuration)/

### intermed dir
../../../bin2/Windows/$(Platform)/$(Configuration)/$(TargetName).tmp\

### C/C++

/GS /analyze- /W3 /Zc:wchar_t /ZI /Gm /Od /Fd"../../../bin2/Windows/Win32/Debug/mol2inchi.tmp\vc140.pdb" /Zc:inline /fp:precise /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "BUILD_LINK_AS_DLL" /D "TARGET_EXE_USING_API=1" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /Fa"../../../bin2/Windows/Win32/Debug/mol2inchi.tmp\" /EHsc /nologo /Fo"../../../bin2/Windows/Win32/Debug/mol2inchi.tmp\" /Fp"../../../bin2/Windows/Win32/Debug/mol2inchi.tmp\mol2inchi.pch" 


### preprocessor defs
WIN32;_DEBUG;_CONSOLE;BUILD_LINK_AS_DLL;TARGET_EXE_USING_API=1;%(PreprocessorDefinitions)
### RTL
Multi-threaded Debug DLL (/MDd)

## Linker

### Output file
../../../bin2/Windows/$(Platform)/$(Configuration)/mol2inchi.exe																			
### Input-Addtl dependencies
kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib; "..\..\..\bin2\windows\$(Platform)\$(Configuration)\libinchi.lib"; "..\..\..\bin2\windows\win32\debug\libinchi.lib";%(AdditionalDependencies)

### Command line

/OUT:"../../../bin2/Windows/Win32/Debug/mol2inchi.exe" /MANIFEST /NXCOMPAT /PDB:"../../../bin2/Windows/Win32/Debug/mol2inchi.pdb" /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" "..\..\..\bin2\windows\Win32\Debug\libinchi.lib" "..\..\..\bin2\windows\win32\debug\libinchi.lib" /STACK:"16000000" /DEBUG /MACHINE:X86 /SAFESEH /INCREMENTAL /PGD:"../../../bin2/Windows/Win32/Debug/mol2inchi.pgd" /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"../../../bin2/Windows/Win32/Debug/mol2inchi.tmp\mol2inchi.exe.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 
