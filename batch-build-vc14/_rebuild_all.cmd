C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" > rebuild_all.log
REM --------------------------------
REM inchi-1.exe
REM --------------------------------
REM
echo call _rebuild_inchi-1.cmd >> rebuild_all.log
call _rebuild_inchi-1.cmd 
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log
REM
REM --------------------------------
REM libinchi
REM --------------------------------
REM
echo call _rebuild_libinchi.cmd >> rebuild_all.log
call _rebuild_libinchi.cmd 
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log
REM
REM --------------------------------
REM mol2inchi
REM --------------------------------
REM
echo call _rebuild_mol2inchi.cmd  >> rebuild_all.log
call _rebuild_mol2inchi.cmd 
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log
REM
REM --------------------------------
REM test_ixa
REM --------------------------------
REM
echo call _rebuild_test_ixa.cmd  >> rebuild_all.log
call _rebuild_test_ixa.cmd 
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log
REM
REM --------------------------------
REM inchi_main
REM --------------------------------
REM
echo call _rebuild_inchi_main.cmd   >> rebuild_all.log
call _rebuild_inchi_main.cmd 
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log
REM
REM
REM
REM
REM
REM
echo grep fail rebuild-*.log  >> rebuild_all.log
grep fail rebuild-*.log  >> rebuild_all.log
REM
C:\PS0\sys\GnuWin32\bin\date.exe --iso-8601="seconds" >> rebuild_all.log

