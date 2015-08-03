#!/bin/bash

make clean
make $@
[ $? -ne 0 ] && exit 1

./testRun.out

