REM Compile 4 gcov, gprof
REM
mingw32-make -f makefile32_cov
REM
REM Run executable
REM
inchi-1-32-cov.exe MMs03263667_2D.mol nul
REM
REM  Create gcov outfiles
REM
gcov ichi_bns.c 
gcov ichimak2.c	
gcov ichiparm.c 
gcov ichiring.c	
gcov ichirvr6.c     
gcov ikey_dll.c
gcov ichi_io.c  
gcov ichimake.c	
gcov ichiprt1.c 
gcov ichirvr1.c	
gcov ichirvr7.c     
gcov runichi.c
gcov ichican2.c 
gcov ichimap1.c
gcov ichiprt2.c 
gcov ichirvr2.c	
gcov ichisort.c     
gcov sha2.c
gcov ichicano.c 
gcov ichimap2.c	
gcov ichiprt3.c 
gcov ichirvr3.c	
gcov ichister.c     
gcov strutil.c
gcov ichicans.c 
gcov ichimap4.c	
gcov ichiqueu.c 
gcov ichirvr4.c	
gcov ichitaut.c     
gcov util.c
gcov ichiisot.c 
gcov ichinorm.c	
gcov ichiread.c 
gcov ichirvr5.c	
gcov ikey_base26.c
gcov debug.c  
gcov dispstru.c  
gcov IChI_lib.c  
gcov ichimain.c  
gcov mol2atom.c  
gcov readinch.c  
gcov readmol.c
