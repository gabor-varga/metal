#!/bin/bash

for file in build/test/* 
do
    if [ $file != "build/test/libcatch.so" ]
    then
        echo "Running test: " $file
        ./$file
    fi
done
