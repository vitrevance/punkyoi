#!/bin/bash

premake5 --file=./lib/SOIL2/premake5.lua gmake
cd ./lib/SOIL2/make/linux/
make config=release_x86_64 soil2-static-lib
cd ../../../../
premake5 gmake
make config=release
cp ./bin/Release/* ./