#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "tree.h"
#include "commands.h"
#include "parse.h"

/* FUNCTION DECLARATIONS */

void handleParameters(int, char**, bool*);

/* FUNCTION DEFINITIONS */

int main(int argc, char** argv) {

	bool isDebugMode;
	handleParameters(argc, argv, &isDebugMode);

	Tree* tree;
	initializeTree(&tree);
	parseInput(tree, isDebugMode);
	destroyTree(tree);

	return 0;
}

// Checks if program runs in debug mode.
// If there are any forbidden parameters, exits the program with code "1".
void handleParameters(	int parameterAmount,
						char** parameterArray,
						bool* isDebugModePointer) {

	// Only parameter is a program name. Not run in debug mode.
	if (parameterAmount == 1) {
		*isDebugModePointer = false;
	}

	// There are more parameters.
	else {

		// Check every parameter beside first.
		for (int i = 1; i < parameterAmount; i++) {

			// Copy parameter to buffer.
			int bufferSize = (strlen(parameterArray[i]) + 1) * sizeof(char);
			char* buffer = (char*) malloc(bufferSize);
			strcpy(buffer, parameterArray[i]);

			// Parameter is "-v".
			if (strcmp(buffer, "-v") == 0) {
				// Run in debug mode.
				*isDebugModePointer = true;
			}

			// ERROR. Parameter is forbidden.
			else {
				printf("ERROR\n");

				// Exit returning 1.
				exit(1);
			}

			// Free buffer's memory.
			free(buffer);
		}
	}
}
