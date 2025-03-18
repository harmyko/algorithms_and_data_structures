@echo off
if .%USERDOMAIN% == .ugniu goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
mingw32-make.exe

:toliau
echo Running test.exe...
test.exe > test.txt
echo Testing finished, results saved to test.txt
pause
