#Runs debug executable
run: 
    ./bin/LichenEngine_debug-windows-x86.exe

#Compiles debug mode
compile:
    mingw32-make -j4


#Compiles and runs release mode
release: 
    mingw32-make config=release -j4
    ./bin/LichenEngine_release-windows-x86.exe

#Compiles and runs profiler mode
profile: 
    mingw32-make config=profiler -j4
    ./bin/LichenEngine_profiler-windows-x86.exe

#Updates makefiles
premake:
    ./premake5 gmake2