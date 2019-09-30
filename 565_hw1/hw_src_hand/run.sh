#! /bin/bash

printf "Running loop_performance code:\n"
./loop_performance 100000000

printf "Running loop_fusion code:\n"
./loop_fusion 100000000

printf "Running loop_reverse code:\n"
./loop_reverse 100000000

printf "Running loop_unroll code:\n"
./loop_unroll 100000000