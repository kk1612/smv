@echo off

IF "%SETUP_IFORT_COMPILER_64%"=="1" GOTO envexist

  set SETUP_IFORT_COMPILER_64=1

  IF DEFINED IFORT_COMPILER14 set IFORT_COMPILER=%IFORT_COMPILER14%
  IF DEFINED IFORT_COMPILER15 set IFORT_COMPILER=%IFORT_COMPILER15%
  IF DEFINED IFORT_COMPILER16 set IFORT_COMPILER=%IFORT_COMPILER16%
  IF DEFINED IFORT_COMPILER17 set IFORT_COMPILER=%IFORT_COMPILER17%
  IF DEFINED IFORT_COMPILER18 set IFORT_COMPILER=%IFORT_COMPILER18%
  IF DEFINED IFORT_COMPILER19 set IFORT_COMPILER=%IFORT_COMPILER19%

  IF NOT DEFINED IFORT_COMPILER (
    echo "*** Error: Intel IFORT_COMPILER environment variable not defined."
  )
  IF DEFINED IFORT_COMPILER (
    if exist "%IFORT_COMPILER%\bin\ifortvars.bat" (
      echo Setting up Fortran compiler environment
      call "%IFORT_COMPILER%\bin\ifortvars" intel64
    )
    if not exist "%IFORT_COMPILER%\bin\ifortvars.bat" (
      echo.
      echo ***warning: compiler setup script,
      echo    "%IFORT_COMPILER%\bin\ifortvars.bat",
      echo    does not exist
      echo.
    )
  )

  IF DEFINED ICPP_COMPILER14 set ICPP_COMPILER=%ICPP_COMPILER14%
  IF DEFINED ICPP_COMPILER15 set ICPP_COMPILER=%ICPP_COMPILER15%
  IF DEFINED ICPP_COMPILER16 set ICPP_COMPILER=%ICPP_COMPILER16%
  IF DEFINED ICPP_COMPILER17 set ICPP_COMPILER=%ICPP_COMPILER17%
  IF DEFINED ICPP_COMPILER18 set ICPP_COMPILER=%ICPP_COMPILER18%
  IF DEFINED ICPP_COMPILER19 set ICPP_COMPILER=%ICPP_COMPILER19%

  IF DEFINED ICPP_COMPILER (
    if exist "%ICPP_COMPILER%\bin\iclvars.bat" (
      echo Setting up C/C++ compiler environment
      call "%ICPP_COMPILER%\bin\iclvars" intel64
    )
    if not exist "%ICPP_COMPILER%\bin\iclvars.bat" (
      echo.
      echo ***warning compiler setup script,
      echo    "%ICPP_COMPILER%\bin\iclvars.bat",
      echo    does not exist
      echo.
    )
  )

  IF NOT DEFINED I_MPI_ROOT (
    echo "*** Error: Intel MPI environment variable, I_MPI_ROOT, not defined."
    echo "    Intel MPI development environment probably not installed."
    exit /b
  )

  echo Setting up MPI environment
  set "I_MPI_ROOT=%I_MPI_ROOT_SAVE%"
  set I_MPI_RELEASE_ROOT=%I_MPI_ROOT%\intel64\lib
  set   I_MPI_DEBUG_ROOT=%I_MPI_ROOT%\intel64\lib
  IF DEFINED IFORT_COMPILER19 set I_MPI_RELEASE_ROOT=%I_MPI_ROOT%\intel64\lib\release
  IF DEFINED IFORT_COMPILER19 set I_MPI_DEBUG_ROOT=%I_MPI_ROOT%\intel64\lib\debug
  call "%I_MPI_ROOT%\intel64\bin\mpivars" release

:envexist
