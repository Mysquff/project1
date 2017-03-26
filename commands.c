#include "tree.h"

/* COMMAND FUNCTIONS DECLARATIONS */

// ADD_NODE
void commandAddNode(Tree*, int);

/* COMMAND FUNCTIONS DEFINITIONS */

// ADD_NODE
void commandAddNode(Tree* tree, int parentIndex) {
	addTreeNode(tree, parentIndex);
}
