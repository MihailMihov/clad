#!/bin/bash
clang-18 -Ofast -Xclang -add-plugin -Xclang clad -Xclang -load -Xclang ../../../build/lib/clad.so -I../../../include/ -x c++ -std=c++14 -lstdc++ -lm cpp-smallpt.cpp -fopenmp=libomp -o cpp-smallpt "$@"
clang-18 -Ofast -Xclang -add-plugin -Xclang clad -Xclang -load -Xclang ../../../build/lib/clad.so -I../../../include/ -x c++ -std=c++14 -lstdc++ -lm diff-tracer-1.cpp -fopenmp=libomp -o diff-tracer-1 "$@"
