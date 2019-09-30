#! /bin/bash

gcc -O2 -o bandwidth_test bandwidth_test.c


printf "Running bandwidth test (L1 write only):\n"
./bandwidth_test 1 4096 100000

printf "Running bandwidth test (L1 1:1 read-to-write):\n"
./bandwidth_test 2 4096 100000

printf "Running bandwidth test (L1 2:1 read-to-write):\n"
./bandwidth_test 3 4096 100000


printf "Running bandwidth test (L3 write only):\n"
./bandwidth_test 1 3300000 500

printf "Running bandwidth test (L3 1:1 read-to-write):\n"
./bandwidth_test 2 3300000 500

printf "Running bandwidth test (L3 2:1 read-to-write):\n"
./bandwidth_test 3 3300000 500