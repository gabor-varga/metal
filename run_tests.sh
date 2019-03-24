#!/bin/bash

for file in build/tests/unit/* 
do
    if [ $file != "build/tests/unit/libcatch.so" ]
    then
        echo "Running test: " $file
        ./$file
    fi
done
