#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=$PREFIX -S . -G Ninja -B build
ninja -C build install
