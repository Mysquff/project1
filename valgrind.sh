#!/bin/sh
make debug
valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./solution.gdb
