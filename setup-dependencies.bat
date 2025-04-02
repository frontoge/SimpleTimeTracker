@echo off
cd vcpkg || echo vcpkg directory not found && exit /b 1
call .\bootstrap-vcpkg.bat
call .\vcpkg install boost-serialization
echo Dependencies installed. You can now build the project.