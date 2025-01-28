cmake -S . -G "Visual Studio 16 2019" ^ -D CMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% -D CMAKE_BUILD_TYPE=Release -B build
if errorlevel 1 exit 1

cmake --build build --target install
if errorlevel 1 exit 1
