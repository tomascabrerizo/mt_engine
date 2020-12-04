@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
g++ -o engine ..\code\App.cpp  -lgdi32  -luser32 -lkernel32 -lWinmm -lopengl32
REM cl /EHsc -Zi ..\code\App.cpp gdi32.lib  user32.lib kernel32.lib Winmm.lib opengl32.lib
popd
