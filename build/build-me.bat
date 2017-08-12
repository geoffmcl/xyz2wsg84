@setlocal
@REM ############################################
@REM NOTE: SPECIAL INSTALL LOCATION
@REM Adjust to suit your environment
@REM ##########################################
@set VCVER=14
@set TMPINST=X:\3rdParty.x64
@REM set TMPINST=F:\Projects\software.x64
@if NOT EXIST %TMPINST%\nul goto NOINST

@set TMPOPTS=-DCMAKE_INSTALL_PREFIX=%TMPINST% -DBUILD_SHARED_LIB:BOOL=OFF
@set TMPOPTS=%TMPOPTS% -G "Visual Studio %VCVER% Win64"
@set TMPPRJ=xyz2wsg84
@set TMPSRC=..
@echo Build %TMPPRJ% project, in 64-bits
@set TMPLOG=bldlog-1.txt
@set BLDDIR=%CD%
@set ADDINST=0

@call chkmsvc %TMPPRJ%

@set SET_BAT=%ProgramFiles(x86)%\Microsoft Visual Studio %VCVER%.0\VC\vcvarsall.bat
@if NOT EXIST "%SET_BAT%" goto NOBAT

@echo Doing build output to %TMPLOG%
@echo Doing build output to %TMPLOG% > %TMPLOG%
@echo Doing: 'call "%SET_BAT%" AMD64'
@echo Doing: 'call "%SET_BAT%" AMD64' >> %TMPLOG%
@call "%SET_BAT%" AMD64 >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR0

@REM call setupqt64
@cd %BLDDIR%

@echo Begin %DATE% %TIME%, output to %TMPLOG%
@echo Begin %DATE% %TIME% >> %TMPLOG%

@echo Doing: 'cmake %TMPSRC% %TMPOPTS%'
@echo Doing: 'cmake %TMPSRC% %TMPOPTS%' >> %TMPLOG%
@cmake %TMPSRC% %TMPOPTS% >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR1

@echo Doing: 'cmake --build . --config debug'
@echo Doing: 'cmake --build . --config debug' >> %TMPLOG%
@cmake --build . --config debug >> %TMPLOG%
@if ERRORLEVEL 1 goto ERR2

@echo Doing: 'cmake --build . --config release'
@echo Doing: 'cmake --build . --config release' >> %TMPLOG%
@cmake --build . --config release >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR3

@echo Appears a successful build
@echo.
@if "%ADDINST%x" == "1x" goto DOINST
@echo Install not configured. Set ADDINST=1
@echo.
@goto END
:DOINST
@echo Continue with install to %TMPINST%? Only Ctrl+c aborts...
@echo.
@pause

@echo Doing: 'cmake --build . --config Debug  --target INSTALL'
@echo Doing: 'cmake --build . --config Debug  --target INSTALL' >> %TMPLOG%
@cmake --build . --config Debug  --target INSTALL >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR4

@if EXIST install_manifest.txt (
@copy install_manifest.txt install_manifest_dbg.txt >nul
)

@echo Doing: 'cmake --build . --config Release  --target INSTALL'
@echo Doing: 'cmake --build . --config Release  --target INSTALL' >> %TMPLOG%
@cmake --build . --config Release  --target INSTALL >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR5

@if EXIST install_manifest.txt (
@copy install_manifest.txt install_manifest_rel.txt >nul
)

@echo ==============================================
@fa4 " -- " %TMPLOG%
@echo All done %TMPPRJ% - Build and install - see %TMPLOG% for details...

@goto END

:NOBAT
@echo Can NOT locate MSVC setup batch "%SET_BAT%"! *** FIX ME ***
@goto ISERR

:ERR0
@echo MSVC 10 setup error
@goto ISERR

:ERR1
@echo cmake config, generation error
@goto ISERR

:ERR2
@echo debug build error
@goto ISERR

:ERR3
@echo release build error
@goto ISERR

:ERR4
@echo debug install error
@goto ISERR

:ERR5
@echo release install error
@goto ISERR

:NOINST
@echo NOT EXIST %TMPINST%\nul! *** FIX ME ***
@echo Is X: drive setup?
@goto ISERR

:ISERR
@endlocal
@exit /b 1

:END
@endlocal
@exit /b 0

@REM eof
