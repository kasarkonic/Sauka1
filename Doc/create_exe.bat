@echo on
REM path to Qt bin
cd C:\Qt\6.7.2\mingw_64\bin
REM set enviroment
call qtenv2.bat
REM path to application exe file
cd C:\SVN\MMMsvn\Sauka1\build\Desktop_Qt_6_7_2_MinGW_64_bit-Release\release
REM call deploy 
call C:\Qt\6.7.2\mingw_64\bin\windeployqt.exe Saukas_kudra.exe
pause

