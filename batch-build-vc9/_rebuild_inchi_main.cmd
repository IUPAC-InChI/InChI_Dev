SET ACT=/Build
REM SET ACT=/Rebuild
SET NAM=inchi_main
SET SLN=I:\_ipl\INCHI\devel\INCHI-DEV\INCHI-1-SRC\INCHI_API\demos\inchi_main\vc9\inchi_main.vcproj
REM sln 
SET BLD= C:\PROGRA~2\MICROS~1.0\COMMON7\IDE\devenv.com
del rebuild-%NAM%.log
%BLD% %SLN% %ACT% "Debug|Win32" /Out rebuild-%NAM%.log
%BLD% %SLN% %ACT% "Debug|x64" /Out rebuild-%NAM%.log
%BLD% %SLN% %ACT% "Release|Win32" /Out rebuild-%NAM%.log
%BLD% %SLN% %ACT% "Release|x64" /Out rebuild-%NAM%.log
