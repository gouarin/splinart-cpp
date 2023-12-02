#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX -S . -G Ninja -B build
ninja -C build install
