#!/bin/bash
code=$1
g++ ${code}.cpp -o $code -std=c++20 -g -DDeBuG -Wall -Wshadow -fsanitize=address,undefined && ./$code
