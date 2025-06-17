@echo off
setlocal
set prog=%1
g++ %prog%.cpp -o %prog% -DDeBuG -std=c++17 -g -Wall -Wshadow && .\%prog% 
endlocal