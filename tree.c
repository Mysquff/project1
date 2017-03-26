#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "tree.h"

#define MAXIMUM_NUMBER_OF_NODES 500100

struct Tree {
	int nodesAmount;

	Node** nodesArray;
};

/* DECLARATIONS */
void initializeTree(Tree**);
void destroyTree(Tree*);
void destroyTreeNodeByIndex(Tree*, int);
Node* getTreeNodeByIndex(Tree*, int);
void addTreeNode(Tree*, int);
int getTreeNodesAmount(Tree*);
int getIndexOfRightmostChild(Tree*, int);
void deleteTreeNodeByIndex(Tree*, int);

// Initializes tree.
void initializeTree(Tree** treePointer) {
	// Allocate tree.
	(*treePointer) = (Tree*) malloc(sizeof (Tree));

	// Temporary pointers.
	Tree* tree = (*treePointer);

	// Allocate nodes array.
	int arraySize = (sizeof (Node*)) * MAXIMUM_NUMBER_OF_NODES;
	tree->nodesArray = (Node**) malloc (arraySize);

	// Initialize root node.
	Node** rootPointer = &(tree->nodesArray[0]);
	initializeNode(rootPointer, 0);

	// Set nodes amount to 1.
	tree->nodesAmount = 1;
}

// Destroys tree and frees its memory.
void destroyTree(Tree* tree) {

	// Destroy all tree nodes.
	for (int i = 0; i < tree->nodesAmount; i++) {
		destroyTreeNodeByIndex(tree, i);
	}

	// Destroy the nodes array.
	free(tree->nodesArray);

	// At last, destroy the tree.
	free(tree);
}

// Returns a pointer to the node by its index.
Node* getTreeNodeByIndex(Tree* tree, int index) {
	return tree->nodesArray[index];
}

// Adds new node to the tree.
void addTreeNode(Tree* tree, int parentIndex) {

	// Initialize new node.
	Node* node;
	initializeNode(&node, tree->nodesAmount);

	// Place new node at the end of the nodes array.
	(tree->nodesArray)[tree->nodesAmount] = node;

	// Increase number of nodes.
	(tree->nodesAmount)++;

	// Put node into parent's children list.
	Node* parent = getTreeNodeByIndex(tree, parentIndex);
	AddNodeToParent(parent, node);
}

// Returns number of nodes in the tree.
int getTreeNodesAmount(Tree* tree) {
	return tree->nodesAmount;
}

// Returns an index of a rightmost child. If a child doesn't exist, returns -1.
int getIndexOfRightmostChild(Tree* tree, int parentIndex) {

	Node* parent = getTreeNodeByIndex(tree, parentIndex);
	Node* rightmostChild = getRightmostChild(parent);

	if (rightmostChild) {
		return getIndex(rightmostChild);
	}

	else {
		return -1;
	}
}

// Deletes node and puts its children in its place.
void deleteTreeNodeByIndex(Tree* tree, int index) {

	Node* node = getTreeNodeByIndex(tree, index);

	// Delete node from its parent's list and put children in its place.
	deleteNode(node);

	// Delete node from nodes array and free its memory.
	destroyTreeNodeByIndex(tree, index);

}

void destroyTreeNodeByIndex(Tree* tree, int index) {

	Node* node = getTreeNodeByIndex(tree, index);

	if (node) {

		// Delete node from nodes array.
		tree->nodesArray[index] = NULL;

		// Free its memory.
		free(node);
	}
}
