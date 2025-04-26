@echo off

if .%USERDOMAIN% == .ugniu goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe

goto :toliau

:savasPC
echo Running on personal PC
mingw32-make

:toliau
echo Running tests...

rem Test with input from file
echo ... > test1.txt
airport_sim.exe - < test1.txt > result1.txt

rem Test cases
airport_sim.exe -test > result2.txt

echo All tests completed