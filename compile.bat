@echo off
echo 🏥 Hospital Management System - Windows Compiler
echo ===============================================

:: Check if g++ is available
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo.
    echo ❌ ERROR: g++ compiler not found!
    echo.
    echo Please install MinGW-w64 and make sure it's in your PATH.
    echo.
    echo 📥 Download from: https://www.mingw-w64.org/
    echo.
    echo 🔧 Installation steps:
    echo 1. Download MinGW-w64 installer
    echo 2. Run the installer
    echo 3. Select Architecture: x86_64
    echo 4. Install to: C:\MinGW
    echo 5. Add C:\MinGW\bin to your system PATH
    echo.
    echo After installation, restart Command Prompt and try again.
    echo.
    pause
    exit /b 1
)

echo.
echo ✅ g++ compiler found!
echo.

:: Create build directory if it doesn't exist
if not exist "build" mkdir build

echo 🔨 Compiling source files...
echo.

:: Compile the project
g++ -std=c++11 -Wall -g -Isrc -o build/hospital_system.exe src/main.cpp src/hospitalsystem.cpp

:: Check if compilation was successful
if %errorlevel% neq 0 (
    echo.
    echo ❌ COMPILATION FAILED!
    echo Please check the errors above and fix your code.
    echo.
    pause
    exit /b 1
)

echo.
echo ✅ COMPILATION SUCCESSFUL!
echo.
echo 🚀 Executable created: build\hospital_system.exe
echo.

:: Ask if user wants to run the program
set /p run="Do you want to run the program now? (y/n): "
if /i "%run%"=="y" (
    echo.
    echo Starting Hospital Management System...
    echo =====================================
    echo.
    build\hospital_system.exe
) else (
    echo.
    echo You can run the program later with: build\hospital_system.exe
    echo.
)

pause
