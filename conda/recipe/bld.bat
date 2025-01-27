cmake -S . -G "Visual Studio 17 2022" -D CMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% -D CMAKE_BUILD_TYPE=Release -B build
if errorlevel 1 exit 1

ninja -C build install
if errorlevel 1 exit 1
