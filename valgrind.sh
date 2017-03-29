#!/bin/sh

for f in tests/*.in; do
	valgrind > /dev/null --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./solution.gdb > /dev/null < $f
	if [ "$?" = "15" ]; then
		echo $f
	fi
done
