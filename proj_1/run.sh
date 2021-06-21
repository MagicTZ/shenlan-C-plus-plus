#! /bin/bash

repo_root_path=$(pwd)
cd ${repo_root_path}
if [ -d "build" ];  then
    rm -rf build
fi
mkdir -p build
cd build
cmake ..
make  -j6
