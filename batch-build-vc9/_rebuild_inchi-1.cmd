SET NAM=inchi-1
SET SLN=I:\_ipl\INCHI\devel\INCHI-DEV\INCHI-1-SRC\INCHI_EXE\inchi-1\vc9\inchi-1.sln
SET BLD= C:\PROGRA~2\MICROS~1.0\COMMON7\IDE\devenv.com
del rebuild-%NAM%.log
%BLD% %SLN% /Rebuild "Debug|Win32" /Out rebuild-%NAM%.log
%BLD% %SLN% /Rebuild "Debug|x64" /Out rebuild-%NAM%.log
%BLD% %SLN% /Rebuild "Release|Win32" /Out rebuild-%NAM%.log
%BLD% %SLN% /Rebuild "Release|x64" /Out rebuild-%NAM%.log
