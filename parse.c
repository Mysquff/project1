#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "tree.h"
#include "commands.h"

#define MAX_COMMAND_NAME_LENGTH 16

void parseInput(Tree* tree, bool isDebugMode) {

	char buffer[MAX_COMMAND_NAME_LENGTH];

	// Run while there is input.
	while (scanf("%s", buffer) != EOF) {

		int parameter1, parameter2;

		// Select command based on imput.
		Command command = selectCommand(buffer);

		// Run selected command.
		switch (command) {

			case COMMAND_ADD_NODE:
				scanf("%d", &parameter1);
				commandAddNode(tree, parameter1);
				printf("OK\n");
			break;

			case COMMAND_RIGHTMOST_CHILD:
				scanf("%d", &parameter1);
				commandRightmostChild(tree, parameter1);
			break;

			case COMMAND_DELETE_NODE:
				scanf("%d", &parameter1);
				commandDeleteNode(tree, parameter1);
				printf("OK\n");
			break;

			case COMMAND_DELETE_SUBTREE:
				scanf("%d", &parameter1);
				commandDeleteSubtree(tree, parameter1);
				printf("OK\n");
			break;

			case COMMAND_SPLIT_NODE:
				scanf("%d %d", &parameter1, &parameter2);
				// commandSplitNode(tree, parameter1, parameter2);
				printf("OK\n");
			break;

			default:
			case COMMAND_UNKNOWN:
				// Asserts command is allowed.
				assert(true);
			break;
		}

		// Debug mode. Print nodes amount to stderr.
		if(isDebugMode) {
			int nodesAmount = getTreeNodesAmount(tree);
			fprintf(stderr, "NODES: %d\n", nodesAmount);
		}

	}
}
