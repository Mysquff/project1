#include <stdio.h>

#include "tree.h"

/* COMMAND FUNCTIONS DECLARATIONS */

void commandAddNode(Tree*, int);
void commandRightmostChild(Tree*, int);

/* COMMAND FUNCTIONS DEFINITIONS */

// ADD_NODE
void commandAddNode(Tree* tree, int parentIndex) {
	addTreeNode(tree, parentIndex);
	printf("OK\n");
}

// RIGHTMOST_CHILD
void commandRightmostChild(Tree* tree, int parentIndex) {
	int rightmostChildIndex = getRightmostChildIndex(tree, parentIndex);
	printf("%d\n", rightmostChildIndex);
}
