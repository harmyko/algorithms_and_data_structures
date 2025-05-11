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
echo Running tests...
(
echo Vilnius Barcelona
echo Vilnius Warsaw 07:15 65
echo Vilnius Frankfurt 08:30 135
echo Warsaw Berlin 09:45 55
echo Warsaw Prague 10:30 60
echo Frankfurt Paris 11:20 75
echo Frankfurt Rome 12:15 110
echo Berlin Amsterdam 13:40 80
echo Paris Barcelona 14:30 90
echo Rome Barcelona 15:45 120
echo Amsterdam Barcelona 16:20 140
echo Prague Vienna 09:25 45
echo Vienna Rome 11:40 85
) > test1.txt

rem Perform tests with input from file
flight_router.exe - < test1.txt > result1.txt

rem Test cases
flight_router.exe -test > result2.txt
echo All tests completed

pause
