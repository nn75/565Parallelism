#! /bin/bash

 gcc -O2 -o matrix_test matrix_test.c


printf "Running i-j-k loop code:\n"
./matrix_test ijk

# printf "Running j-k-i loop code:\n"
# ./matrix_test jki

# printf "Running i-k-j loop code:\n"
# ./matrix_test ikj

printf "Running i-k-j loop tiling code:\n"
./matrix_test ijk-t