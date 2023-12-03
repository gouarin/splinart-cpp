cmake -S . -G "Ninja" -D CMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% -D CMAKE_BUILD_TYPE=Release -B build
if errorlevel 1 exit 1

ninja -C build install
if errorlevel 1 exit 1
