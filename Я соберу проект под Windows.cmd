cmake -S . -B build
cd build
cmake --build . --config debug
debug\proxy.exe
pause
