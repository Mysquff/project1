#!/bin/bash

### Check parameters.

# There are fewer than 2 parameters.
if (( $# < 2 )); then
	# Error. Too few parameters.
	echo "$0: Script was executed with too few parameters."
	exit 1

# There are 2 parameters.
elif (( $# == 2 )); then
	# Script wasn't executed in debug mode.
	debug_mode=false
	program="$1"
	directory="$2"

# There are 3 parameters.
elif (( $# == 3 )); then
	if [ "$1" = "-v" ]; then
		# Script was executed in debug mode.
		debug_mode=true
		program="$2"
		directory="$3"
	else
		# Error. Too many parameters.
		echo "$0: Script was executed with too many parameters."
		exit 1
	fi

# There are more than 3 parameters.
else
	# Error. Too many parameters.
	echo "$0: Script was executed with too many parameters."
	exit 1
fi

### Run tests.

failed_tests=()
failed_debug_tests=()

for filename in "$directory"/*.in; do

	# Get testname from filename.
	testname=${filename#$directory/}
	testname=${testname%.in}

	# Check if output for selected input differs from model output.
	command=$(./"$program" < "$filename" | diff -q - "${filename%.in}".out)

	# There are errors from diff command.
	if [[ -n $command ]]; then
		# Add current test to failed tests list.
		failed_tests+=( "$testname" )
	fi

	# Check for errors in debug mode.
	if [ "$debug_mode" = true ]; then
		# Change command, so it passes only stderr to diff
		# and compares it with .err files.
		command=$(./"$program" -v < "$filename" 2>&1 > /dev/null | diff -q - "${filename%.in}".err)

		# There are errors from diff command.
		if [[ -n $command ]]; then
			# Add current test to failed debug tests list.
			failed_debug_tests+=( "$testname" )
		fi
	fi

done

### Print tests results.

if [ "$failed_tests" != "" ]; then
	echo "Failed tests: ${failed_tests[@]}"
fi

if [ "$failed_debug_tests" != "" ]; then
	echo "Failed debug tests: ${failed_debug_tests[@]}"
fi
