REM
SET EXEC=inchi-1.exe 
SET PAT104=N:\INCHI\ref\distrib\1.04\_inchi-104-files-downloaded-2014-02-09\INCHI-1-BIN\windows\32bit\
SET PAT105=N:\INCHI\devel\INCHI-DEV\INCHI-1-SRC\INCHI_EXE\bin\Windows\Win32\Release\
REM
SET NAM=qqwe
REM
%PAT104%%EXEC% %NAM% %NAM%.std01.inchi-1-104.out %NAM%.std01.inchi-1-104.log NUL /Key /SDF:CAS_RN
%PAT105%%EXEC% %NAM% %NAM%.std01.inchi-1-105.out %NAM%.std01.inchi-1-105.log NUL /Key /SDF:CAS_RN 
grep "InChI=" %NAM%.std01.inchi-1-104.out > %NAM%.std01.inchi-1-104.inc
grep "InChI=" %NAM%.std01.inchi-1-105.out > %NAM%.std01.inchi-1-105.inc
grep "AuxInfo=" %NAM%.std01.inchi-1-104.out > %NAM%.std01.inchi-1-104.aux
grep "AuxInfo=" %NAM%.std01.inchi-1-105.out > %NAM%.std01.inchi-1-105.aux
diff -s %NAM%.std01.inchi-1-104.inc %NAM%.std01.inchi-1-105.inc > diff-105-104-%NAM%.std01.inc
grep -c "\-\-\-" diff-105-104-%NAM%.std01.inc > diff-105-104-%NAM%.std01.inc-count
diff -s %NAM%.std01.inchi-1-104.aux %NAM%.std01.inchi-1-105.aux > diff-105-104-%NAM%.std01.aux
grep -c "\-\-\-" diff-105-104-%NAM%.std01.aux > diff-105-104-%NAM%.std01.aux-count
REM
SET NAM=ITS.sdf
REM
%PAT104%%EXEC% %NAM% %NAM%.std01.inchi-1-104.out %NAM%.std01.inchi-1-104.log NUL /Key /SDF:CAS_RN
%PAT105%%EXEC% %NAM% %NAM%.std01.inchi-1-105.out %NAM%.std01.inchi-1-105.log NUL /Key /SDF:CAS_RN 
grep "InChI=" %NAM%.std01.inchi-1-104.out > %NAM%.std01.inchi-1-104.inc
grep "InChI=" %NAM%.std01.inchi-1-105.out > %NAM%.std01.inchi-1-105.inc
grep "AuxInfo=" %NAM%.std01.inchi-1-104.out > %NAM%.std01.inchi-1-104.aux
grep "AuxInfo=" %NAM%.std01.inchi-1-105.out > %NAM%.std01.inchi-1-105.aux
diff -s %NAM%.std01.inchi-1-104.inc %NAM%.std01.inchi-1-105.inc > diff-105-104-%NAM%.std01.inc
grep -c "\-\-\-" diff-105-104-%NAM%.std01.inc > diff-105-104-%NAM%.std01.inc-count
diff -s %NAM%.std01.inchi-1-104.aux %NAM%.std01.inchi-1-105.aux > diff-105-104-%NAM%.std01.aux
grep -c "\-\-\-" diff-105-104-%NAM%.std01.aux > diff-105-104-%NAM%.std01.aux-count
REM
