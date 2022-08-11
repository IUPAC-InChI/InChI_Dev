REM --------------------------------
REM inchi-1.exe
REM --------------------------------
REM
call _rebuild_inchi-1.cmd 
REM
REM --------------------------------
REM libinchi
REM --------------------------------
REM
call _rebuild_libinchi.cmd 
REM
REM --------------------------------
REM mol2inchi
REM --------------------------------
REM
call _rebuild_mol2inchi.cmd 
REM
REM --------------------------------
REM test_ixa
REM --------------------------------
REM
call _rebuild_test_ixa.cmd 
REM
REM --------------------------------
REM inchi_main
REM --------------------------------
REM
call _rebuild_inchi_main.cmd 
REM
grep fail rebuild*.log
REM
