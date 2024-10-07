@echo off
setlocal

REM Устанавливаем флаг выхода при ошибке
set "ERRORLEVEL=0"

REM Проверяем, существует ли каталог build
if exist "build" (
    echo Removing existing build directory...
    rmdir /s /q "build"
)

echo Create build directory...
mkdir build

cd build

echo Start CMake
cmake ..

if %ERRORLEVEL% neq 0 (
    echo CMake failed
    exit /b %ERRORLEVEL%
)

cmake --build .

if %ERRORLEVEL% neq 0 (
    echo Build failed
    exit /b %ERRORLEVEL%
)

REM Запускаем приложение
.\PENISYUIPIZDA228AGAAGA.exe

endlocal
