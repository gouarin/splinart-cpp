#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX -S . -DCMAKE_INSTALL_LIBDIR=lib -B build
cmake --build build --target install
