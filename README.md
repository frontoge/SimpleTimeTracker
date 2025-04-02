# Overview
This is a simple cross platform tool that allows for time tracking of projects. Currently this is only a CLI tool.

# Upcoming Features
- Loading and saving to custom files
- Categorizing Projects
- Windows Makefile
- GUI

# Development

## Prerequesites
- Git
- CMake
- C++ compiler (duh)

## Clone repo
This repository includes vcpkg as a submodule. When cloning please use
`git clone --recurse-submodules`

If you did not do this run the following after cloning:
`git submodule update --init`

## Install dependencies
On *nix run `./setup-dependencies.sh` on windows run `setup-dependencies.bat`

## Build Instructions
```
cmake --preset=vcpkg
cmake --build ./build
```

# Running
After a build has been downloaded or compiled all you have to do is run the executable that was created in `./build/`