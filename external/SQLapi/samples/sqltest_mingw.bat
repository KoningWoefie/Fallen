@echo off
rem set path=c:\Dev-Cpp\bin;%PATH%
rem set PATH=C:\Program Files\CodeBlocks\MinGW\bin;%PATH%
rem set path=C:\Program Files (x86)\CodeBlocks\MinGW\bin;%PATH%
rem set path=c:\mingw\bin;%PATH%
rem set PATH=D:\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin;%PATH%
rem set PATH=D:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin;%PATH%
set path=d:\mingw\9.2\bin;%PATH%

rem ***********************************
rem Special build configuration defines
rem ***********************************
rem CFG=(relese|debug)
rem CFG_LINK=(dynamic|static)
rem OBJS - specify test program object file (sqltest.obj by default)
rem ***********************************
rem SA_64BIT		build 64-bit version
rem SA_32BIT		build 32-bit version
rem ***********************************

set SA_OPTIONS=SA_32BIT=1 SA_UNICODE=1

echo ------------------------
echo --- Building release ---
echo ------------------------
mingw32-make -f Makefile.mingw %SA_OPTIONS% CFG=release CFG_LINK=dynamic safe_clean all	
mingw32-make -f Makefile.mingw %SA_OPTIONS% CFG=release CFG_LINK=static safe_clean all	

echo ----------------------
echo --- Building debug ---
echo ----------------------
mingw32-make -f Makefile.mingw %SA_OPTIONS% CFG=debug CFG_LINK=dynamic safe_clean all	
mingw32-make -f Makefile.mingw %SA_OPTIONS% CFG=debug CFG_LINK=static safe_clean all	
