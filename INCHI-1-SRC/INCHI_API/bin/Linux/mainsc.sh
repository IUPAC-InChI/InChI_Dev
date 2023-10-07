#!/bin/bash
mypath="$(pwd)"
# mypath=/path/to/directory_with_libinchi.so.1
export LD_LIBRARY_PATH=$mypath:${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}