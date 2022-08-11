REM
echo *** MOL *** 
echo *** MOL *** >>timing
del ..\..\mol\*.*.txt
echo %time% >>timing
inchi-1-32-prof.exe ..\..\mol\*.MOL /AMI /AMILogStd /AMIPrbNone /AuxNone 2>nul
echo %time% >>timing
echo *** END MOL *** >>timing
echo *** END MOL ***
del ..\..\mol\*.*.txt
