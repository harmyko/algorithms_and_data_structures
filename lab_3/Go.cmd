@echo off

rem === Compilation ===
if .%USERDOMAIN% == .ugniu goto :savasPC
rem MIF computer
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
echo Running on personal PC
mingw32-make

:toliau
echo.

rem
echo airport_sim.exe will be run with the parameters from tests.txt. 
echo Edit the text file to run your own tests.
pause

echo Running airport_sim.exe with parameters from tests.txt file.
airport_sim.exe -test

echo.
echo Done. Results have been saved to results.txt as well.
pause
