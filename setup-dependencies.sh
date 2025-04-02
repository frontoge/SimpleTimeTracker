#!/bin/bash
cd vcpkg || { echo "vcpkg directory not found"; exit 1; }

./bootstrap-vcpkg.sh
./vcpkg install boost-serialization

echo "Dependencies installed. You can now build the project."
