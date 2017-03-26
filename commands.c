#include <stdio.h>

#include "tree.h"

/* COMMAND FUNCTIONS DECLARATIONS */

void commandAddNode(Tree*, int);
void commandRightmostChild(Tree*, int);
void commandDeleteNode(Tree*, int);

/* COMMAND FUNCTIONS DEFINITIONS */

// ADD_NODE
void commandAddNode(Tree* tree, int parentIndex) {
	addTreeNode(tree, parentIndex);
	//printf("OK\n");
}

// RIGHTMOST_CHILD
void commandRightmostChild(Tree* tree, int parentIndex) {
	int rightmostChildIndex = getIndexOfRightmostChild(tree, parentIndex);
	printf("%d\n", rightmostChildIndex);
}

// DELETE_NODE
void commandDeleteNode(Tree* tree, int index) {
	deleteTreeNodeByIndex(tree, index);
	//printf("OK\n");
}
