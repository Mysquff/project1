#!/bin/sh

### Script to test whether a program prodeuces any errors
### while running under valgrind.

# Make sure solution.gdb exists.
make debug

# Run tests.
for f in tests/*.in; do
	valgrind 2> /dev/null --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./solution.dbg > /dev/null < $f
	if [ "$?" = "15" ]; then
		echo $f
	fi
done
