#!/bin/bash

if [[ $UID != 0 ]]; then
    echo "Please run this script with sudo:"
    echo "sudo $0 $*"
    exit 1
fi

echo "Building Release"
echo "Fetching requirements"
set echo off
apt-get install libglew-dev -y -qq > /dev/null
apt-get install libglfw3 -y -qq > /dev/null
apt-get install libglfw3-dev -y -qq > /dev/null
set echo on
echo "Building"
make config=release_x86_64
make clean
echo "Done"