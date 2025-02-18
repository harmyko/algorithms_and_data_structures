@echo off
if .%USERDOMAIN% == .ugniu goto :savasPC

echo Aptiktas fakulteto kompiuteris...
set PATH=C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%PATH%
mingw32-make.exe
goto :execute

:savasPC
echo Aptiktas asmeninis kompiuteris...
make

:execute
test.exe > test.txt
echo Programa baigė savo darbą, išvestis įrašyta į test.txt.
