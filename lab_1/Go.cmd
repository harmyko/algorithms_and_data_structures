@echo off
if .%USERDOMAIN% == .ugniu goto :savasPC

set PATH=C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%PATH%
mingw32-make.exe
goto :execute

:savasPC
make

:execute
test.exe > test.txt
echo Results have been saved to test.txt
