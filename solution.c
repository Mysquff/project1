#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

// Maximum length of a command name on input including string terminator.
#define MAX_COMMAND_STRING_LENGTH 16

// Pointer to a command function.
typedef void (*CommandPointer)(Tree*, int, int);

/* FUNCTION DECLARATIONS */

// Prints error message and ends program returning 0. */
void errorExit();

// Checks if program was launched in debug mode.
// Also if there are any forbidden arguments, ends program in error mode.
bool isDebugMode(int, char**);

printNodesAmount(Tree*) {

}

// Selects command function and returns pointer to it.
CommandPointer selectCommand(char*, int*, int*);

// Runs command functions based on input.
void handleInput(Tree*, bool);

/* COMMAND FUNCTIONS DECLARATIONS */

// ADD_NODE
void commandAddNode(Tree*, int);

// RIGHTMOST_CHILD
void commandRightmostChild( Tree*, int);

// DELETE_NODE
void commandDeleteNode(Tree*, int);

// DELETE_SUBTREE
void commandDeleteSubtree(Tree*, int);

// SPLIT_NODE
void commandSplitNode(Tree*, int, int);

/* FUNCTION DEFINITIONS */

void errorExit() {
	printf("ERROR\n");
	return 0;
}

bool isDebugMode(int numberOfArguments, char** argumentsArray) {

	// Argument check result.
	typedef enum { NORMAL, DEBUG, ERROR } Result;
	Result result;

	// There's only program name argument.
	if (numberOfArguments == 1) {
		result = NORMAL;
	}

	// There are additional arguments.
	else {

		int i = 0;

		while (i < numberOfArguments && result != ERROR) {

			// Calculate necessary buffer size.
			int bufferSize = strlen(argumentsArray[i]) + 1) * sizeof(char);

			// Allocate buffer and copy argument's string into it. */
			char* buffer = (char*) malloc(bufferSize);
			strcpy(buffer, argumentsArray[i]);

			// Debug mode argument.
			if (strcmp(buffer, "-v") == 0) {
				result = DEBUG;
			}

			// Forbidden argument.
			else {
				result = ERROR;
			}

			// Free buffer.
			free(buffer);

			i++;
	    }
	}

	// Handle result.
	switch (result) {
		case NORMAL:
			return false;

		case DEBUG:
			return true;

		case ERROR:
			errorExit();
	}

}

CommandPointer selectCommand(
	char* commandName,
	int* parameter1,
	int* parameter2) // only necessary in SPLIT_NODE command
{
	CommandPointer commandFunction;

	// ADD_NODE
	if (strcmp(commandName, "ADD_NODE") == 0) {
		commandPointer = &commandAddNode;
		scanf("%d", parameter1);
	}

	// RIGHTMOST_CHILD
	else if (strcmp(commandName, "RIGHTMOST_CHILD") == 0) {
		commandPointer = &commandRightmostChild;
		scanf("%d", parameter1);
	}

	// DELETE_NODE
	else if (strcmp(commandName, "DELETE_NODE") == 0) {
		commandPointer = &commandDeleteNode;
		scanf("%d", parameter1);
	}

	// DELETE_SUBTREE
	else if (strcmp(commandName, "DELETE_SUBTREE") == 0) {
		commandPointer = &commandDeleteSubtree;
		scanf("%d", parameter1);
	}

	// SPLIT_NODE
	else if (strcmp(commandName, "SPLIT_NODE") == 0) {
		commandPointer = &commandSplitNode;
		scanf("%d", parameter1);
		scanf("%d", parameter2);
	}

	// Wrong command
	else {
		errorExit();
	}

	return commandPointer;
}

void handleInput(Tree* tree, bool debugMode) {

	char commandName[MAX_COMMAND_STRING_LENGTH];
	int parameter1, parameter2;

	while (scanf("%s", commandName) != -1) {

		// Select command function.
		CommandPointer commandPointer;
		commandPointer = selectCommand(commandName, &parameter1, &parameter2);

		// Run selected command function.
		(*commandPointer)(tree, parameter1, parameter2);
	}

	if (debugMode) {
		printNodesAmount(tree);
	}
}

/* COMMAND FUNCTIONS DEFINITIONS */

// ADD_NODE
void commandAddNode(Tree* tree, int parentIndex) {
	addTreeNode(tree, parentIndex);
}


int main(int argc, char** argv) {

	bool debugMode = isDebugMode(argc, argv);

	Tree tree;
	initializeTree(&tree);

	// Handle comamnds on input.
	handeInput(&tree, debugMode);

	return 0;
}
