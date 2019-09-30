#! /bin/bash

printf "Running non-unrolled loop code:\n"
./loop 3 100000000

printf "\nRunning unrolled loop code:\n"
./unroll 3 100000000
