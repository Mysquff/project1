#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "commands.h"

/* COMMAND FUNCTIONS DECLARATIONS */

Command selectCommand(char*);
void commandAddNode(Tree*, int);
void commandRightmostChild(Tree*, int);
void commandDeleteNode(Tree*, int);
void commandDeleteSubtree(Tree*, int);

/* COMMAND FUNCTIONS DEFINITIONS */

// Selects command based on string.
Command selectCommand(char* string) {

	// ADD_NODE
	if (strcmp(string, "ADD_NODE") == 0) {
		return COMMAND_ADD_NODE;
	}

	// RIGHTMOST_CHILD
	else if (strcmp(string, "RIGHTMOST_CHILD") == 0) {
		return COMMAND_RIGHTMOST_CHILD;
	}

	// DELETE_NODE
	else if (strcmp(string, "DELETE_NODE") == 0) {
		return COMMAND_DELETE_NODE;
	}

	// DELETE_SUBTREE
	else if (strcmp(string, "DELETE_SUBTREE") == 0) {
		return COMMAND_DELETE_SUBTREE;
	}

	// SPLIT_NODE
	else if (strcmp(string, "SPLIT_NODE") == 0) {
		return COMMAND_SPLIT_NODE;
	}

	// Unknown command.
	else {
		return COMMAND_UNKNOWN;
	}

}

// ADD_NODE
void commandAddNode(Tree* tree, int parentIndex) {
	addTreeNode(tree, parentIndex);
}

// RIGHTMOST_CHILD
void commandRightmostChild(Tree* tree, int parentIndex) {
	int rightmostChildIndex;
	rightmostChildIndex = getRightmostChildIndexByParentIndex(tree, parentIndex);
	printf("%d\n", rightmostChildIndex);
}

// DELETE_NODE
void commandDeleteNode(Tree* tree, int index) {
	deleteTreeNodeByIndex(tree, index);
}

// DELETE_SUBTREE
void commandDeleteSubtree(Tree* tree, int subtreeRootIndex) {
	deleteSubtreeByIndex(tree, subtreeRootIndex);
}

// SPLIT_NODE
void commandSplitNode(Tree* tree, int parentIndex, int leftNeighbourIndex) {
	splitTreeNodeByIndex(tree, parentIndex, leftNeighbourIndex);
}
