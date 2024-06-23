@echo off

rem Register Environment variables for Borland C++
rem Register Environment variables for Borland C++
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\RAD Studio\11.0"
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\RAD Studio\12.0"
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\Studio\14.0"
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\Studio\15.0"
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\Studio\19.0"
rem set BCCDIR="C:\Program Files (x86)\Embarcadero\Studio\20.0"
set BCCDIR="C:\Program Files (x86)\Embarcadero\Studio\21.0"
PATH=%BCCDIR%\Bin

rem ***********************************
rem Special build configuration defines
rem ***********************************
rem CFG=(relese|debug)
rem CFG_LINK=(dynamic|static)
rem SA_RUNTIME=(dynamic|static)
rem SA_UNICODE		build UNICODE version
rem OBJS		specify test program object file (sqltest.obj by default)
rem SA_64BIT		build 64-bit version
rem ***********************************
set SA_OPTIONS=SA_32BIT=1

echo ------------------------
echo --- Building release ---
echo ------------------------
make /f Makefile.bcc %SA_OPTIONS% CFG=release CFG_LINK=dynamic safe_clean all
make /f Makefile.bcc %SA_OPTIONS% CFG=release CFG_LINK=static safe_clean all

echo ----------------------
echo --- Building debug ---
echo ----------------------
make /f Makefile.bcc %SA_OPTIONS% CFG=debug CFG_LINK=dynamic safe_clean all
make /f Makefile.bcc %SA_OPTIONS% CFG=debug CFG_LINK=static safe_clean all

