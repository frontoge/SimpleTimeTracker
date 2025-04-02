#!/bin/bash
cd vcpkg || { echo "vcpkg directory not found"; exit 1; }

./bootstrap-vcpkg.sh
cd .. && ./vcpkg/vcpkg install

echo "Dependencies installed. You can now build the project."
